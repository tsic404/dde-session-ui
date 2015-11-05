#include <QtCore/QObject>
#include <QDebug>
#include <QSettings>
#include <QFile>
#include <QKeyEvent>

#include "constants.h"
#include "passwdedit.h"

PassWdEdit::PassWdEdit(QString iconId, QWidget* parent)
    : QFrame(parent)
{
    m_iconId = iconId;
    initUI();
    initConnect();
    initData();
    setObjectName("passwdEnterFrame");
    setFixedSize(QSize(DDESESSIONCC::PASSWDLINEEIDT_WIDTH, 36));
}

PassWdEdit::~PassWdEdit()
{
}

void PassWdEdit::initUI() {
    m_keyboardButton = new QPushButton;
    m_keyboardButton->setObjectName("KeyBoardLayoutButton");

    m_keyboardButton->setFixedSize(QSize(24, 24));
    m_iconButton = new QPushButton;
    m_iconButton->setObjectName(m_iconId);
    m_iconButton->setCheckable(true);
    m_iconButton->setFixedSize(QSize(34, 34)); // 34 = 36 - borderTop - borderBottom
    m_iconButton->setIconSize(QSize(34, 34));

    m_lineEdit = new QLineEdit;
    m_lineEdit->setObjectName("passwdLineEdit");
    m_lineEdit->setEchoMode(QLineEdit::Password);
    m_lineEdit->setFixedHeight(m_iconButton->height());
    m_lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    m_Layout = new QHBoxLayout;
    m_Layout->setMargin(0);
    m_Layout->setSpacing(0);
    m_Layout->addSpacing(3);
    m_Layout->addWidget(m_keyboardButton);
    m_Layout->addWidget(m_lineEdit);
    m_Layout->addStretch();
    m_Layout->addWidget(m_iconButton);
    setLayout(m_Layout);

}

void PassWdEdit::initConnect() {
    connect(m_iconButton, &QPushButton::clicked, this, &PassWdEdit::submit);
    connect(m_keyboardButton, &QPushButton::clicked, this, &PassWdEdit::keybdLayoutButtonClicked);

}

void PassWdEdit::initData() {
    utilSettings = new UtilSettings(this);
}

void PassWdEdit::focusInEvent(QFocusEvent *)
{
    m_lineEdit->setFocus();
}

void PassWdEdit::updateKeybordLayoutStatus(const QString &username)
{

    keyboardLayoutList = utilSettings->getKbdLayoutList(username);
    if (keyboardLayoutList.isEmpty()) {
        keyboardLayoutList << "";
    }
    qDebug() << "get UpdateKeybordLayoutStatus";

    if (keyboardLayoutList.count() > 2) {
        m_keyboardButton->show();
    } else {
        m_keyboardButton->hide();
    }
    emit updateKeyboardStatus();
}
void PassWdEdit::updateKeybdLayoutUI(QStringList keybdList) {
    if (keybdList.count() > 2) {
        m_keyboardButton->show();
    } else {
        m_keyboardButton->hide();
    }
}

void PassWdEdit::keyReleaseEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Return:        /* submit */
    case Qt::Key_Enter:         emit submit();              break;
    default:;
    }
}

void PassWdEdit::setLineEditRightImage(QString imageUrl) {
    m_iconButton->setIcon(QIcon(QPixmap(imageUrl)));
}

QString PassWdEdit::getText() {
    return m_lineEdit->text();
}