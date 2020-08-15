#ifndef CUSTOMER_BNUB
#define CUSTOMER_BNUB
#include "User.h"
#include "Order.h"
#include <QVector>
class Customer :
	public User
{
protected:
private:
	const int mode = 0;
	QDateTime birthday;
	QString phone_number;
    QVector<QString> order_ids;
	QVector<QString> addresses;
public:
    int getMode() const;
    Customer(QString username, QString password, QDateTime _birthday, QString _phone_number);
	void setBirthday(QDateTime birthday);
	QDateTime getBirthday() const;
	void setPhoneNumber(QString phone_number);
    QVector<QString> getOrderIds() const;
    QString getPhoneNumber() const;
    QVector<QString> getAddresses() const;
	void addAddress(QString address);
	void removeAddressAt(int at);
    int buy(QVector<Item> my_basket);
    void sell(QString good_id, QString color, QString number);

};

#endif
