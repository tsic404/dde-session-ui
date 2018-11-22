#ifndef USERINPUTWIDGET_H
#define USERINPUTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <DPasswdEditAnimated>
#include <QPushButton>
#include <functional>
#include <darrowrectangle.h>

#include "useravatar.h"
#include "framedatabind.h"

DWIDGET_USE_NAMESPACE

class KbLayoutWidget;
class UserInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit UserInputWidget(QWidget *parent = nullptr);

    void setName(const QString &name);
    void setAvatar(const QString &avatar);
    void setIsNoPasswordGrp(bool isNopassword);
    void setFaildMessage(const QString &message);
    void setFaildTipMessage(const QString &message);
    void updateKBLayout(const QStringList &list);
    void setDefaultKBLayout(const QString &layout);

    void shutdownMode();
    void normalMode();
    void restartMode();

    void grabKeyboard();
    void releaseKeyboard();

    void hideKeyboard();

signals:
    void requestAuthUser(const QString &password);
    void abortOperation();
    void requestUserKBLayoutChanged(const QString &layout);

protected:
    bool event(QEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private:
    void refreshLanguage();
    void refreshAvatarPosition();
    void toggleKBLayoutWidget();
    void refreshKBLayoutWidgetPosition();
    void onOtherPagePasswordChanged(const QVariant &value);
    void onOtherPageKBLayoutChanged(const QVariant &value);

private:
    UserAvatar *m_userAvatar;
    QLabel *m_nameLbl;
    DPasswdEditAnimated *m_passwordEdit;
    QPushButton *m_loginBtn;
    DArrowRectangle *m_kbLayoutBorder;
    KbLayoutWidget *m_kbLayoutWidget;
    std::list<std::pair<std::function<void (QString)>, QString>> m_trList;
};

#endif // USERINPUTWIDGET_H