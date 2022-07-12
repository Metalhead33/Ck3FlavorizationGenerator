#include "Flavorization.hpp"
#include <QTextStream>

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
static const QString FEUDAL = QStringLiteral("feudal");
static const QString REPUBLIC = QStringLiteral("republic");
static const QString TRIBAL = QStringLiteral("tribal");
static const QString FEUDAL_GOV = QStringLiteral("feudal_government");
static const QString TRIBAL_GOV = QStringLiteral("tribal_government");

static QString flagsToName(int governments)
{
	if(governments == FLAG_REPUBLIC) return REPUBLIC;
	else if(governments == FLAG_TRIBAL) return TRIBAL;
	else return FEUDAL;
}

QString Flavorization::getTitle() const
{
	if(isTitle) {
		if(tier == PRINCE) return QStringLiteral("%1_%2_%3_independent").arg(tierToTitle(tier),flagsToName(governments),name);
		else return QStringLiteral("%1_%2_%3").arg(tierToTitle(tier),flagsToName(governments),name);
	} else {
		if(isHeir) return QStringLiteral("%1_heir_%2_%3_%4").arg(tierToHolder(tier),
																 flagsToName(governments),
																 isFemale ? QStringLiteral("female") : QStringLiteral("male"),name); // count_feudal_female_hungarian
		else return QStringLiteral("%1_%2_%3_%4").arg(tierToHolder(tier),
														   flagsToName(governments),														   isFemale ? QStringLiteral("female") : QStringLiteral("male"),name); // count_feudal_female_hungarian
	}
}

/*
	bool isTitle;
	bool isFemale;
	bool isHeir;
	Tier tier;
	int governments;
	QString name;
	QString locString;
	QString getTitle() const;
	QStringList name_lists, religions, heritages;
*/
Flavorization::Flavorization(const QStringList& tags, const QString& str)
{
	faulty = false;
	priorityOffset = 0;
	this->isHeir = false;
	if(tags.contains(QStringLiteral("of"))) {
		this->isTitle = true;
		if(tags.contains(QStringLiteral("barony"))) this->tier = BARONY;
		else if(tags.contains(QStringLiteral("county"))) this->tier = COUNTY;
		else if(tags.contains(QStringLiteral("duchy"))) this->tier = DUCHY;
		else if(tags.contains(QStringLiteral("kingdom"))) this->tier = KINGDOM;
		else if(tags.contains(QStringLiteral("empire"))) this->tier = EMPIRE;
		else faulty = true;
	} else {
		this->isTitle = false;
		if(tags.contains(QStringLiteral("baron"))) this->tier = BARONY;
		else if(tags.contains(QStringLiteral("count"))) this->tier = COUNTY;
		else if(tags.contains(QStringLiteral("duke"))) this->tier = DUCHY;
		else if(tags.contains(QStringLiteral("king"))) this->tier = KINGDOM;
		else if(tags.contains(QStringLiteral("emperor"))) this->tier = EMPIRE;
		else if(tags.contains(QStringLiteral("prince"))) {
			this->tier = KINGDOM;
			this->isHeir = true;
		}
		else faulty = true;
	}
	if(tags.contains(QStringLiteral("female"))) this->isFemale = true;
	else this->isFemale = false;
	this->governments = 0;
	if(tags.contains(QStringLiteral("city"))) this->governments |= FLAG_REPUBLIC;
	if(tags.contains(QStringLiteral("tribal")) || tags.contains(QStringLiteral("nomadic")))
	{
		this->governments |= FLAG_TRIBAL;
		++priorityOffset;
	}
	if(!this->governments) this->governments = FLAG_CLAN | FLAG_FEUDAL;
	if(!(this->governments & FLAG_REPUBLIC) && (this->tier == KINGDOM || this->tier == EMPIRE)) this->governments |= FLAG_TRIBAL;
	this->locString = str;
	this->name = tags.back();
	this->name_lists.push_back( QStringLiteral("name_list_%1").arg(this->name));
	locString = locString.remove(QStringLiteral(" of"));
}

void Flavorization::outputDefinition(QTextStream& stream) const
{
	if(faulty) return;
	stream << getTitle() << " = {\n\t";
	stream << "type = "<< (isTitle ? "title" : "character") << "\n\t";
	if(!isTitle) {
		stream << "gender = "<< (isFemale ? "female" : "male") << "\n\t";
		stream << "special = "<< (isHeir ? "ruler_child" : "holder") << "\n\t";
	}
	stream << "tier = "<< tierToTitle(tier) << "\n\t";
	stream << "priority = "<< (isHeir ? int(tier)-4 : int(tier))+priorityOffset <<"\n\t";
	stream << "governments = { ";
	if(governments & FLAG_FEUDAL) stream << "feudal_government ";
	if(governments & FLAG_TRIBAL) stream << "tribal_government ";
	if(governments & FLAG_CLAN) stream << "clan_government ";
	if(governments & FLAG_REPUBLIC) stream << "republic_government ";
	stream << "}\n";
	if(religions.size()) {
		stream << "\treligions = { ";
		for(const auto& it : religions) stream << it << ' ';
		stream << "}\n";
	}
	if(name_lists.size()) {
		stream << "\tname_lists = { ";
		for(const auto& it : name_lists) stream << it << ' ';
		stream << "}\n";
	}
	if(heritages.size()) {
		stream << "\theritages = { ";
		for(const auto& it : heritages) stream << it << ' ';
		stream << "}\n";
	}
	if(!isTitle) stream << "\ttop_liege = no"<< "\n";
	if(tier == PRINCE) stream << "\tonly_independent = yes\n";
	stream << "}";
}

void Flavorization::outputLocalization(QTextStream& stream) const
{
	if(faulty) return;
	stream << ' ' << getTitle() << ":0 \"" << locString << '\n';
}
