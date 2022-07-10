#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <QFile>
#include <QMap>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextCodec>

static QTextStream STDOUT(stdout);
enum Tier {
	BARONY,
	COUNTY,
	DUCHY,
	KINGDOM,
	EMPIRE,
	PRINCE
};
QString generateFlavorizationTitleHolder(Tier htier, bool female, const QString& culture, bool heir = false);
QString generateFlavorizationTitleTitle(Tier htier, const QString& culture);
QString generateFlavorizationHolder(Tier htier,  bool female, const QString& culture, bool heir = false);
QString generateFlavorizationTitle(Tier htier, const QString& culture);
struct CultureTitles {
	QString cultureName;
	QString BARONY, BARON_MALE, BARON_FEMALE;
	QString COUNTY, COUNT_MALE, COUNT_FEMALE;
	QString DUCHY, DUKE_MALE, DUKE_FEMALE;
	QString KINGDOM, KING_MALE, KING_FEMALE;
	QString EMPIRE, EMPEROR_MALE, EMPEROR_FEMALE;
	QString PRINCE_MALE, PRINCE_FEMALE;
	QString IDUKE, IDUKE_MALE, IDUKE_FEMALE;
	void output(QTextStream& localizationStream, QTextStream& definitionsStream) const {
		localizationStream << " # " << cultureName << '\n';
		definitionsStream << "# " << cultureName << '\n';
		if( !BARONY.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::BARONY,cultureName) << ":1 \"" << BARONY << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::BARONY,cultureName) << '\n';
		}
		if( !BARON_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::BARONY,false,cultureName) << ":1 \"" << BARON_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::BARONY,false,cultureName) << '\n';
		}
		if( !BARON_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::BARONY,true,cultureName) << ":1 \"" << BARON_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::BARONY,true,cultureName) << '\n';
		}
		if( !COUNTY.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::COUNTY,cultureName) << ":1 \"" << COUNTY << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::COUNTY,cultureName) << '\n';
		}
		if( !COUNT_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::COUNTY,false,cultureName) << ":1 \"" << COUNT_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::COUNTY,false,cultureName) << '\n';
		}
		if( !COUNT_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::COUNTY,true,cultureName) << ":1 \"" << COUNT_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::COUNTY,true,cultureName) << '\n';
		}
		if( !DUCHY.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::DUCHY,cultureName) << ":1 \"" << DUCHY << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::DUCHY,cultureName) << '\n';
		}
		if( !DUKE_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::DUCHY,false,cultureName) << ":1 \"" << DUKE_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::DUCHY,false,cultureName) << '\n';
		}
		if( !DUKE_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::DUCHY,true,cultureName) << ":1 \"" << DUKE_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::DUCHY,true,cultureName) << '\n';
		}
		if( !KINGDOM.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::KINGDOM,cultureName) << ":1 \"" << KINGDOM << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::KINGDOM,cultureName) << '\n';
		}
		if( !KING_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::KINGDOM,false,cultureName) << ":1 \"" << KING_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::KINGDOM,false,cultureName) << '\n';
		}
		if( !KING_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::KINGDOM,true,cultureName) << ":1 \"" << KING_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::KINGDOM,true,cultureName) << '\n';
		}
		if( !EMPIRE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::EMPIRE,cultureName) << ":1 \"" << EMPIRE << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::EMPIRE,cultureName) << '\n';
		}
		if( !EMPEROR_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::EMPIRE,false,cultureName) << ":1 \"" << EMPEROR_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::EMPIRE,false,cultureName) << '\n';
		}
		if( !EMPEROR_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::EMPIRE,true,cultureName) << ":1 \"" << EMPEROR_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::EMPIRE,true,cultureName) << '\n';
		}
		if( !IDUKE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleTitle(Tier::PRINCE,cultureName) << ":1 \"" << IDUKE << "\"\n";
			definitionsStream << generateFlavorizationTitle(Tier::PRINCE,cultureName) << '\n';
		}
		if( !IDUKE_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::PRINCE,false,cultureName) << ":1 \"" << IDUKE_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::PRINCE,false,cultureName) << '\n';
		}
		if( !IDUKE_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::PRINCE,true,cultureName) << ":1 \"" << IDUKE_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::PRINCE,true,cultureName) << '\n';
		}
		if( !PRINCE_MALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::KINGDOM,false,cultureName,true) << ":1 \"" << PRINCE_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::KINGDOM,false,cultureName,true) << '\n';
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::EMPIRE,false,cultureName,true) << ":1 \"" << PRINCE_MALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::EMPIRE,false,cultureName,true) << '\n';
		}
		if( !PRINCE_FEMALE.isEmpty() ) {
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::KINGDOM,true,cultureName,true) << ":1 \"" << PRINCE_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::KINGDOM,true,cultureName,true) << '\n';
			localizationStream << ' ' << generateFlavorizationTitleHolder(Tier::EMPIRE,true,cultureName,true) << ":1 \"" << PRINCE_FEMALE << "\"\n";
			definitionsStream << generateFlavorizationHolder(Tier::EMPIRE,true,cultureName,true) << '\n';
		}
	}
};
typedef QMap<QString,CultureTitles> TitleMap;

QString tierToHolder(Tier htier)
{
	switch (htier) {
		case BARONY: return QStringLiteral("baron");
		case COUNTY: return QStringLiteral("count");
		case DUCHY: return QStringLiteral("duke");
		case KINGDOM: return QStringLiteral("king");
		case EMPIRE: return QStringLiteral("emperor");
		case PRINCE: return QStringLiteral("prince");
	}
}
QString tierToTitle(Tier htier)
{
	switch (htier) {
		case BARONY: return QStringLiteral("barony");
		case COUNTY: return QStringLiteral("county");
		case DUCHY: return QStringLiteral("duchy");
		case KINGDOM: return QStringLiteral("kingdom");
		case EMPIRE: return QStringLiteral("empire");
		case PRINCE: return QStringLiteral("duchy");
	}
}
QString gender(bool female)
{
	return female ? QStringLiteral("female") : QStringLiteral("male");
}
QString generateFlavorizationTitleHolder(Tier htier, bool female, const QString& culture, bool heir)
{
	if(heir) {
		return QStringLiteral("%3_heir_%2_%1").arg(culture,gender(female),tierToHolder(htier));
	} else {
		if(htier == PRINCE) {
			return QStringLiteral("%3_feudal_%2_%1_independent").arg(culture,gender(female),tierToHolder(DUCHY));
		} else {
			return QStringLiteral("%3_feudal_%2_%1").arg(culture,gender(female),tierToHolder(htier));
		}
	}
}
QString generateFlavorizationTitleTitle(Tier htier, const QString& culture)
{
	if(htier == PRINCE) {
		return QStringLiteral("%1_feudal_%2_independent").arg(tierToTitle(DUCHY));
	} else {
		return QStringLiteral("%1_feudal_%2").arg(tierToTitle(htier),culture);
	}
}
QString generateFlavorizationHolder(Tier htier,  bool female, const QString& culture, bool heir)
{
	if(heir) {
		return QStringLiteral("%3_heir_%2_%1 = {\r"
							  "\n"
							  "\ttype = character\r"
							  "\n"
							  "\tgender = %2\r\n"
							  "\ttier = %4\r\n"
							  "\tspecial = ruler_ch"
							  "ild\r\n"
							  "\tpriority = 36\r\n"
							  "\tgovernments = { fe"
							  "udal_government }\r\n"
							  "\tname_lists = { nam"
							  "e_list_%1 }\r\n"
							  "\ttop_liege = no\r\n"
							  "}").arg(culture,gender(female),tierToHolder(htier),tierToTitle(htier));
	} else {
		if(htier == PRINCE) {
			return QStringLiteral("%3_feudal_%2_%1_independent = {"
								  "\r\n"
								  "\ttype = character\r"
								  "\n"
								  "\tgender = %2\r\n"
								  "\tspecial = holder\r"
								  "\n"
								  "\ttier = %4\r\n"
								  "\tpriority = 28\r\n"
								  "\tonly_independent ="
								  " yes\r\n"
								  "\tgovernments = { fe"
								  "udal_government }\r\n"
								  "\tname_lists = { nam"
								  "e_list_%1 }\r\n"
								  "\ttop_liege = no\r\n"
								  "}").arg(culture,gender(female),tierToHolder(DUCHY),tierToTitle(htier));
		} else {
			return QStringLiteral("%3_feudal_%2_%1 = {"
								  "\r\n"
								  "\ttype = character\r"
								  "\n"
								  "\tgender = %2\r\n"
								  "\tspecial = holder\r"
								  "\n"
								  "\ttier = %4\r\n"
								  "\tpriority = 18\r\n"
								  "\tgovernments = { fe"
								  "udal_government }\r\n"
								  "\tname_lists = { nam"
								  "e_list_%1 }\r\n"
								  "\ttop_liege = no\r\n"
								  "}").arg(culture,gender(female),tierToHolder(htier),tierToTitle(htier));
		}
	}
}
QString generateFlavorizationTitle(Tier htier, const QString& culture)
{
	if(htier == PRINCE) {
	return QStringLiteral("%1_feudal_%2_indepen"
						  "dent = {\r\n"
						  "\ttype = title\r\n"
						  "\ttier = %3\r\n"
						  "\tpriority = 36\r\n"
						  "\tgovernments = { fe"
						  "udal_government tribal"
						  "_government }\r\n"
						  "\tonly_independent ="
						  " yes\r\n"
						  "\tname_lists = { nam"
						  "e_list_%2 }\r\n"
						  "}").arg(tierToTitle(htier),culture,tierToTitle(DUCHY));
	} else {
		return QStringLiteral("%1_feudal_%2 = {\r\n"
							  "\ttype = title\r\n"
							  "\ttier = %1\r\n"
							  "\tpriority = 28\r\n"
							  "\ttop_liege = no\r\n"
							  "\tgovernments = { fe"
							  "udal_government }\r\n"
							  "\tname_lists = { nam"
							  "e_list_%2 }\r\n"
							  "}").arg(tierToTitle(htier),culture);
	}
}

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
	for(auto it = std::begin(titlemap); it != std::end(titlemap); ++it) {
		it.value().output(localizationStream,definitionsStream);
	}
	localizationStream.flush();
	definitionsStream.flush();
	localization_file.flush();
	definitions_file.flush();
	localization_file.close();
	definitions_file.close();
}

void processTitles(const QJsonObject& obj)
{
	TitleMap titles;
	for(auto it = std::begin(obj); it != std::end(obj); ++it) {
		if(!it->isObject()) continue;
		STDOUT << it.key() << '\n';
		QJsonObject obj2 = it->toObject();
		CultureTitles ttl;
		ttl.cultureName = it.key();
		ttl.BARONY = obj2["BARONY"].toString();
		ttl.BARON_MALE = obj2["BARON_MALE"].toString();
		ttl.BARON_FEMALE = obj2["BARON_FEMALE"].toString();
		ttl.COUNTY = obj2["COUNTY"].toString();
		ttl.COUNT_MALE = obj2["COUNT_MALE"].toString();
		ttl.COUNT_FEMALE = obj2["COUNT_FEMALE"].toString();
		ttl.DUCHY = obj2["DUCHY"].toString();
		ttl.DUKE_MALE = obj2["DUKE_MALE"].toString();
		ttl.DUKE_FEMALE = obj2["DUKE_FEMALE"].toString();
		ttl.KINGDOM = obj2["KINGDOM"].toString();
		ttl.KING_MALE = obj2["KING_MALE"].toString();
		ttl.KING_FEMALE = obj2["KING_FEMALE"].toString();
		ttl.EMPIRE = obj2["EMPIRE"].toString();
		ttl.EMPEROR_MALE = obj2["EMPEROR_MALE"].toString();
		ttl.EMPEROR_FEMALE = obj2["EMPEROR_FEMALE"].toString();
		ttl.PRINCE_MALE = obj2["PRINCE_MALE"].toString();
		ttl.PRINCE_FEMALE = obj2["PRINCE_FEMALE"].toString();
		ttl.IDUKE = obj2["IDUKE"].toString();
		ttl.IDUKE_MALE = obj2["IDUKE_MALE"].toString();
		ttl.IDUKE_FEMALE = obj2["IDUKE_FEMALE"].toString();
		titles.insert(it.key(),ttl);
	}
	createTitles(titles);
}

void processTitles()
{
	QFile jsonfile("cultural_titles.json");
	if(jsonfile.open(QFile::ReadOnly))
	{
		QJsonObject obj = QJsonDocument::fromJson(jsonfile.readAll()).object();
		processTitles(obj);
	} else {
		STDOUT << "Failed to open cultural_titles.json for reading!\n";
	}
};

QJsonObject generateTitlesFromStr(QTextStream& stream)
{
	QString str;
	QJsonObject obj;
	while(stream.readLineInto(&str))
	{
		if(str.startsWith('#')) continue;
		QStringList comma_separated = str.split(';',Qt::SkipEmptyParts);
		if(comma_separated.size() < 2) continue;
		QStringList tags = comma_separated[0].split('_',Qt::SkipEmptyParts);
		if(tags.contains(QStringLiteral("city"))) continue;
		if(tags.contains(QStringLiteral("temple"))) continue;
		if(tags.contains(QStringLiteral("consort"))) continue;
		// Debugging purposes
		{
			for(const auto& it : qAsConst(tags)) STDOUT << ' ' << it;
			STDOUT << " = "<< comma_separated[1] << '\n';
		}
		QJsonObject tmpObj;
		if(!obj.contains(tags.back())) {
			obj[tags.back()] = tmpObj;
		} else {
			tmpObj = obj[tags.back()].toObject();
		}
		if(tags.contains(QStringLiteral("baron"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("BARON_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("BARON_MALE"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("count"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("COUNT_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("COUNT_MALE"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("duke"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("DUKE_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("DUKE_MALE"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("king"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("KING_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("KING_MALE"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("emperor"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("EMPEROR_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("EMPEROR_MALE"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("prince"))) {
			if(tags.contains(QStringLiteral("female"))) tmpObj.insert(QStringLiteral("PRINCE_FEMALE"),comma_separated[1]);
			else tmpObj.insert(QStringLiteral("PRINCE_MALE"),comma_separated[1]);
		}
		if(tags.contains(QStringLiteral("barony"))) {
			tmpObj.insert(QStringLiteral("BARONY"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("county"))) {
			tmpObj.insert(QStringLiteral("COUNTY"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("duchy"))) {
			tmpObj.insert(QStringLiteral("DUCHY"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("kingdom"))) {
			tmpObj.insert(QStringLiteral("KINGDOM"),comma_separated[1]);
		} else if(tags.contains(QStringLiteral("emperire"))) {
			tmpObj.insert(QStringLiteral("EMPIRE"),comma_separated[1]);
		}
		obj[tags.back()] = tmpObj;
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
		QJsonObject obj = generateTitlesFromStr(stream);
		QFile raww("raw.json");
		if(raww.open(QFile::WriteOnly)) {
			raww.write(QJsonDocument(obj).toJson());
			raww.flush();
			raww.close();
		}
		processTitles(obj);
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
			   << args[0] << " --processTitles       - Creates title flavorizations from cultural_titles.json.\n"
			   << args[0] << " --generateTitles      - Generates from CSV.\n";
		STDOUT.flush();
	}
	else if(args[1] == QStringLiteral("--processTitles")) processTitles();
	else if(args[1] == QStringLiteral("--generateTitles")) generateTitlesFromStr();
	else {
		STDOUT << "Invalid command!\n";
		STDOUT.flush();
	}
	processTitles();
	return 0;
}
