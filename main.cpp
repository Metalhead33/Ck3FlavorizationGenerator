#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextCodec>
#include "Flavorization.hpp"

const QMap<QString,QString> replacements = {
	{ QStringLiteral("bohemian"), QStringLiteral("czech") },
	{ QStringLiteral("castillan"), QStringLiteral("castilian") },
	{ QStringLiteral("cumbric"), QStringLiteral("cumbrian") },
	{ QStringLiteral("khwarezmi"), QStringLiteral("khwarezmian") },
	{ QStringLiteral("leonese"), QStringLiteral("asturleonese") },
	{ QStringLiteral("oghuz"), QStringLiteral("turkish") },
	{ QStringLiteral("romanian"), QStringLiteral("vlach") },
	{ QStringLiteral("icelandic"), QStringLiteral("norse") },
	{ QStringLiteral("frankish"), QStringLiteral("french") },
	{ QStringLiteral("oldfrankish"), QStringLiteral("frankish") },
	{ QStringLiteral("saxon"), QStringLiteral("anglo_saxon") },
	{ QStringLiteral("lowsaxon"), QStringLiteral("saxon") },
	{ QStringLiteral("caucasianavar"), QStringLiteral("caucasian_avar") },
	{ QStringLiteral("sanhaja"), QStringLiteral("butr") }
	//
	// ligurian - cisalpine
};

static QTextStream STDOUT(stdout);
typedef QList<Flavorization> TitleMap;

void createTitles(const TitleMap& titlemap)
{
	QFile localization_file("fecr_titles.yml");
	QFile definitions_file("fecr_titles.txt");
	if(!(localization_file.open(QFile::WriteOnly | QFile::Text) && definitions_file.open(QFile::WriteOnly | QFile::Text))) {
		STDOUT << "Failed to open fecr_titles.yml or fecr_titles.txt for writing!\n";
		return;
	}
	QTextStream localizationStream(&localization_file);
	QTextStream definitionsStream(&definitions_file);
	localizationStream.setGenerateByteOrderMark(true);
	definitionsStream.setGenerateByteOrderMark(true);
	localizationStream << "l_english:\n";
	for(const auto& it : titlemap) {
		it.outputDefinition(definitionsStream);
		definitionsStream << '\n';
		it.outputLocalization(localizationStream);
		localizationStream << '\n';
	}
	localizationStream << " caliph:0 \"\u004b\u0068\u0061\u006c\u0069\u0066\u0061\u0068\"\n";
	localizationStream.flush();
	definitionsStream.flush();
	localization_file.flush();
	definitions_file.flush();
	localization_file.close();
	definitions_file.close();
}

TitleMap generateTitlesFromStr(QTextStream& stream)
{
	QString str;
	TitleMap obj;
	while(stream.readLineInto(&str))
	{
		// Kuninggaktis
		str = str.replace(QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u009a\u0074\u0069\u0065\u006e\u0065"),QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u0161\u0074\u0069\u0065\u006e\u0117"));
		str = str.replace(QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u009a\u0074\u0069\u0073"),QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u0161\u0074\u0069\u0073"));
		str = str.replace(QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u009a\u0074\u0079\u0073\u0074\u0065"),QStringLiteral("\u004b\u0075\u006e\u0069\u0067\u0061\u0069\u006b\u0161\u0074\u0079\u0073\u0074\u0065"));
		// Zupan
		str = str.replace(QStringLiteral("\u008e\u0075\u0070\u0061\u006e"),QStringLiteral("\u017d\u0075\u0070\u0061\u006e"));
		// Ksiaze
		str = str.replace(QStringLiteral("Ksiaze"),QStringLiteral("\u004b\u0073\u0069\u0105\u017c\u0119"));
		str = str.replace(QStringLiteral("Ksiezna"),QStringLiteral("\u004b\u0073\u0069\u0119\u017c\u006e\u0061"));
		str = str.replace(QStringLiteral("Ksiestwo"),QStringLiteral("\u004b\u0073\u0069\u0119\u0073\u0074\u0077\u006f"));
		str = str.replace(QStringLiteral("Plemie of"),QStringLiteral("\u0050\u006c\u0065\u006d\u0069\u0119"));
		// Hungarian Long Oe
		str = str.replace(QChar('?'),QChar(0x0151));
		if(str.startsWith('#')) continue;
		QStringList comma_separated = str.split(';',Qt::SkipEmptyParts);
		if(comma_separated.size() < 2) continue;
		// tengri_pagan
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("west_african_pagan"),QStringLiteral("africanpagan"));
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("tengri_pagan"),QStringLiteral("tengri"));
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("old_frankish"),QStringLiteral("oldfrankish"));
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("low_frankish"),QStringLiteral("lowfrankish"));
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("low_saxon"),QStringLiteral("lowsaxon"));
		comma_separated[0] = comma_separated[0].replace(QStringLiteral("caucasian_avar"),QStringLiteral("caucasianavar"));
		comma_separated[1] = comma_separated[1].replace(QChar('?'),QChar(0x0151));
		QStringList tags = comma_separated[0].split('_',Qt::SkipEmptyParts);
		if(tags.contains(QStringLiteral("gothic"))) continue;
		if(tags.contains(QStringLiteral("norse"))) continue;
		if(tags.contains(QStringLiteral("temple"))) continue;
		if(tags.contains(QStringLiteral("consort"))) continue;
		if(tags.contains(QStringLiteral("group"))) continue;
		auto replaceIt = replacements.find(tags.back());
		if(replaceIt != std::end(replacements)) tags.back() = replaceIt.value();
		// Debugging purposes
		{
			for(const auto& it : qAsConst(tags)) STDOUT << ' ' << it;
			STDOUT << " = "<< comma_separated[1] << '\n';
		}
		Flavorization flav(tags,comma_separated[1]);
		if(flav.name_lists.contains(QStringLiteral("name_list_lithuanian"))) flav.name_lists.push_back(QStringLiteral("name_list_latgalian"));
		if(flav.name_lists.contains(QStringLiteral("name_list_hungarian"))) flav.name_lists.push_back(QStringLiteral("name_list_mogyer"));
		if(flav.name_lists.contains(QStringLiteral("name_list_cumbrian"))) flav.name_lists.push_back(QStringLiteral("name_list_pictish"));
		if(flav.name_lists.contains(QStringLiteral("name_list_french"))) flav.name_lists.push_back(QStringLiteral("name_list_outremer"));
		if(flav.name_lists.contains(QStringLiteral("name_list_scottish"))) flav.name_lists.push_back(QStringLiteral("name_list_gaelic"));
		if(flav.name_lists.contains(QStringLiteral("name_list_greek"))) flav.name_lists.push_back(QStringLiteral("name_list_gothic"));
		if(flav.name_lists.contains(QStringLiteral("name_list_croatian"))) flav.name_lists.push_back(QStringLiteral("name_list_carantanian"));
		if(flav.name_lists.contains(QStringLiteral("name_list_serbian"))) flav.name_lists.push_back(QStringLiteral("name_list_bosnian"));
		if(flav.name_lists.contains(QStringLiteral("name_list_saxon"))) flav.name_lists.push_back(QStringLiteral("name_list_old_saxon"));
		if(flav.name_lists.contains(QStringLiteral("name_list_czech"))) flav.name_lists.push_back(QStringLiteral("name_list_slovien"));
		if(flav.name_lists.contains(QStringLiteral("name_list_ligurian"))) flav.name_lists.push_back(QStringLiteral("name_list_cisalpine"));
		if(flav.name_lists.contains(QStringLiteral("name_list_butr")))
		{
			flav.name_lists.push_back(QStringLiteral("name_list_baranis"));
			flav.name_lists.push_back(QStringLiteral("name_list_zaghawa"));
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_arabic"))) {
			flav.name_lists.clear();
			flav.name_lists.push_back(QStringLiteral("name_list_bedouin"));
			flav.name_lists.push_back(QStringLiteral("name_list_levantine"));
			flav.name_lists.push_back(QStringLiteral("name_list_egyptian"));
			flav.name_lists.push_back(QStringLiteral("name_list_maghrebi"));
			flav.name_lists.push_back(QStringLiteral("name_list_andalusian"));
			flav.name_lists.push_back(QStringLiteral("name_list_yemeni"));
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_polish"))) {
			flav.name_lists.push_back(QStringLiteral("name_list_pommeranian"));
			flav.name_lists.push_back(QStringLiteral("name_list_polabian"));
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_finnish"))) {
			flav.name_lists.push_back(QStringLiteral("name_list_sami"));
			flav.name_lists.push_back(QStringLiteral("name_list_estonian"));
			flav.name_lists.push_back(QStringLiteral("name_list_karelian"));
			flav.name_lists.push_back(QStringLiteral("name_list_vepsian"));
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_mongol"))) {
			flav.name_lists.push_back(QStringLiteral("name_list_buryat"));
			flav.name_lists.push_back(QStringLiteral("name_list_oirat"));
			flav.name_lists.push_back(QStringLiteral("name_list_naiman"));
			flav.name_lists.push_back(QStringLiteral("name_list_kerait"));
			flav.name_lists.push_back(QStringLiteral("name_list_khitan"));
			flav.name_lists.push_back(QStringLiteral("name_list_tuyuhun"));
			flav.name_lists.push_back(QStringLiteral("name_list_jurchen"));
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_pahlavi"))) {
			flav.heritages.push_back(QStringLiteral("heritage_iranian"));
			flav.name_lists.clear();
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_persian"))) {
			flav.heritages.push_back(QStringLiteral("heritage_iranian"));
			flav.religions.push_back(QStringLiteral("islam_religion"));
			flav.name_lists.clear();
			flav.priorityOffset += 1;
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_tengri"))) {
			flav.religions.push_back(QStringLiteral("tengrism_religion"));
			flav.name_lists.clear();
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_turkic"))) {
			flav.heritages.push_back(QStringLiteral("heritage_turkic"));
			flav.priorityOffset -= 4;
			flav.name_lists.clear();
		}
		if(flav.name_lists.contains(QStringLiteral("name_list_africanpagan"))) {
			flav.religions.push_back(QStringLiteral("west_african_bori_religion"));
			flav.religions.push_back(QStringLiteral("west_african_orisha_religion"));
			flav.religions.push_back(QStringLiteral("west_african_religion"));
			flav.name_lists.clear();
		}
		if(!flav.faulty) obj.push_back(flav);
	}
	for(auto& it : obj)
	{
		if(it.name_lists.contains(QStringLiteral("name_list_czech")) && it.tier == COUNTY)
		{
			it.name_lists.removeOne(QStringLiteral("name_list_slovien"));
		}
		if(it.name_lists.contains(QStringLiteral("name_list_croatian")) && it.tier == COUNTY)
		{
			it.name_lists.push_back(QStringLiteral("name_list_slovien"));
		}
		if(it.name_lists.contains(QStringLiteral("name_list_hungarian")))
		{
				if(it.tier == KINGDOM || it.tier == DUCHY)
				{
					if(it.governments & FLAG_FEUDAL) it.governments &= ~(FLAG_CLAN | FLAG_TRIBAL);
					if(it.governments & FLAG_TRIBAL) it.governments |= FLAG_CLAN;
				}
		}
	}
	return obj;
}
void generateTitlesFromStr()
{
	QFile fil("A_Nobletitles.csv");
	QTextCodec *codec1 = QTextCodec::codecForName("ISO 8859-15");
	if(fil.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream stream(&fil);
		if(codec1) stream.setCodec(codec1);
		TitleMap obj = generateTitlesFromStr(stream);
		createTitles(obj);
	} else {
		STDOUT << "Failed to open A_Nobletitles.csv for reading!\n";
	}
}

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QStringList args;
	for(int i = 0; i < argc; ++i) {
		args.push_back(QString::fromLocal8Bit(argv[i]));
	}
	if(args.size() < 2 || args[1] == QStringLiteral("--help")) {
		STDOUT << "Correct usage:\n"
			   << args[0] << " --help                - Brings up this instruction guide\n"
			   << args[0] << " --generateTitles      - Generates from CSV.\n";
		STDOUT.flush();
	}
	else if(args[1] == QStringLiteral("--generateTitles")) generateTitlesFromStr();
	else {
		STDOUT << "Invalid command!\n";
		STDOUT.flush();
	}
	return 0;
}
