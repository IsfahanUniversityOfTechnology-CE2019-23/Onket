#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "User.h"
#include "Admin.h"
#include "Customer.h"
#include "Guest.h"
#include "loginpage.h"
#include "signup.h"
#include "dashboard.h"
#include "menutype.h"
#include "storage.h"
#include "goodpreviewscrollarea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:


public:
    MainWindow(QWidget *parent = nullptr);
    static void setCurrentUser(User* crnt);
    static User* getCurrentUser();
    static Storage& getOnketRepository();
    static void setLoginPage(LoginPage* lgnpg);
    static void setSignupPage(signup* sinup);
    static void setDashboard(Dashboard* dshbrd);
    static void hideMainScrollArea();
    static void showMainScrollArea();
    ~MainWindow();

private slots:
    void on_action_10_triggered();

    void on_action_11_triggered();

    void on_action_triggered();

public slots:
    void updateScrollAreas(const QString& type_id);
    void setupDynomicMenu(QMenu* menu);

private:
    Ui::MainWindow* ui;
    static LoginPage* login_page;
    static signup* signup_page;
    static Dashboard* dashboard;
    static User* current_user;
    static Storage onket_repository;
    static QScrollArea* main_scroll_area;
    MenuType* base_menu = nullptr;
    QWidget* main_center_widget = nullptr;
    QGridLayout* main_lay = nullptr;
    GoodPreviewScrollArea* scroll_price = nullptr, *scroll_discount = nullptr, *scroll_willingness = nullptr;
};
#endif // MAINWINDOW_H
