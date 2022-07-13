#ifndef FLAVORIZATION_HPP
#define FLAVORIZATION_HPP
#include <QString>
#include <QTextStream>

enum Tier {
	BARONY = 7,
	COUNTY = 18,
	DUCHY = 27,
	KINGDOM = 47,
	EMPIRE = 102,
	PRINCE = 46
};
static const int FLAG_FEUDAL = 1;
static const int FLAG_TRIBAL = 2;
static const int FLAG_CLAN = 4;
static const int FLAG_REPUBLIC = 8;

struct Flavorization
{
	bool isTitle;
	bool isFemale;
	bool isHeir;
	Tier tier;
	int governments;
	QString name;
	QString locString;
	QString getTitle() const;
	QStringList name_lists, religions, heritages;
	int priorityOffset;
	bool faulty;
	Flavorization(const QStringList& tags, const QString& str);
	void outputDefinition(QTextStream& stream) const;
	void outputLocalization(QTextStream& stream) const;
};

#endif // FLAVORIZATION_HPP
