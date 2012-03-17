#include <QWidget>
#include <QDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QVariant>
#include <QPalette>
#include <QPixmap>
#include <QObject>
#include <QGraphicsWidget>
#include <QtGui>
#include <QSettings>
#include <QRegExp>
#include <QValidator>
#include <settingengine.h>
#include <QFile>

#include "settingpage.h"

TabDialog::TabDialog()
{
}
TabDialog::TabDialog(QWidget *parent):QDialog(parent)
{

  generalTab = new GeneralTab();
  userDefineTab = new UserDefineTab(this);
  advanceTab = new AdvanceTab();
  generalTab->setAutoFillBackground(true);
  userDefineTab->setAutoFillBackground(true);
  advanceTab->setAutoFillBackground(true);
  QPalette palette;
  palette.setBrush(QPalette::Base, QBrush(QPixmap(":/images/images/Setting_BlueBackground.png")));
  generalTab->setPalette(palette);
  userDefineTab->setPalette(palette);
  advanceTab->setPalette(palette);

  tabWidget=new QTabWidget;
  tabWidget->addTab(generalTab,tr("General"));
  tabWidget->addTab(userDefineTab,tr("UserDefine"));
  tabWidget->addTab(advanceTab,tr("Advance"));

  buttonBox=new QDialogButtonBox(QDialogButtonBox::Save|QDialogButtonBox::Cancel);

  connect(buttonBox,SIGNAL(accepted()),this,SLOT(WriteSetting()));//save
  connect(buttonBox,SIGNAL(rejected()),this,SLOT(reject()));//Cancel

  QVBoxLayout *mainLayout=new QVBoxLayout;
  mainLayout->addWidget(tabWidget);
  mainLayout->addWidget(buttonBox);
  setLayout(mainLayout);
  SettingBackGround();
  setWindowTitle(tr("Setting Dialog"));

  QString aXmlPath("Meteorologist.ini");
  QFileInfo info;
  info.setFile(aXmlPath);
  if(!info.exists())
  {
      WriteSetting();
  }

}
//=============================================================================
void TabDialog::autoRun( bool isAutoRun )
{
    QSettings *reg = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
                        QSettings::NativeFormat);
    QDir *myDir = new QDir;
    QString currentPath = myDir->currentPath();
    if( isAutoRun )
    {
    currentPath += QString(QObject::tr("/Meteorologist.exe"));
    }
    else currentPath = QString(QObject::tr(""));
    reg->setValue("Meteorologist",currentPath);
    delete reg;
    delete myDir;
}
//=============================================================================

void TabDialog::SettingBackGround()
{
    QPalette p = palette();
    QPixmap img( ":/images/images/Setting_BlueBackground.png" );
    p.setBrush( QPalette::Window, QBrush(img) );
    setPalette( p );
}
//=============================================================================
void TabDialog::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->globalPos();
    Pos = event->globalPos()-event->pos();
}
//=============================================================================
void TabDialog::mouseMoveEvent(QMouseEvent *event)
{
    QPoint newPos = event->globalPos();
    QPoint upleft = Pos + newPos - lastPos;
    move(upleft);
}
//=============================================================================
void TabDialog::WriteSetting()
{
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);

    SettingEngine settingEngine;
    QString current = QString::number(advanceTab->ProxyTypeComboBox->currentIndex());
    QString original = settingEngine.getProxyType();
    if(original != current)
    {
       settings->setValue(tr("ProxIpStatus"),current);
       emit ProxyChangedSignal();
    }
    if(original != "0" && original !="3")
    {
        original = (settingEngine.getProxy())->hostName();
        current = advanceTab->IP->text();
        if(original != current)
            settings->setValue(tr("ProxyIp"),current);

        current = advanceTab->PORT->text();
        original = QString::number((settingEngine.getProxy())->port());
        if(original != current)
            settings->setValue(tr("ProxyPort"),current);

        current = advanceTab->UserLineEdit->text();
        original = (settingEngine.getProxy())->user();
        if(original != current)
            settings->setValue(tr("ProxyUser"),current);

        current = advanceTab->PasswordLineEdit->text();
        original = (settingEngine.getProxy())->password();
        if(original != current)
            settings->setValue(tr("ProxyPassword"),current);

     //   current = advanceTab->DomainLineEdit->text();
       // original = (settingEngine.getProxy())[5].toString();
       // if(original != current)
            settings->setValue(tr("Domain"),current);
    }
    current = advanceTab->ServerSelectComboBox->currentText();
    original = settingEngine.getServer();
    if(original != current)
    {
        settings->setValue(tr("Server"),current);
        emit ServerChangedSignal(current);
    }
    settings->setValue(tr("ServerIndex"),advanceTab->ServerSelectComboBox->currentIndex());

    bool AutoBoot = advanceTab->AutoBoot->isChecked();
    if(AutoBoot != settingEngine.isAutoRun())
    {
        settings->setValue(tr("AutoBoot"),AutoBoot);
        emit AutoRunStatusChangedSignal(AutoBoot);
    }
    // settings->setValue(tr("AutoBoot"),AutoBoot);

    current = userDefineTab->DisplayItemNum->currentText();
    original = QString::number(settingEngine.getDisplayedDays());
    if(original != current)
    {
        settings->setValue(tr("DaysDisplayed"),current);
        emit DisplayedDaysChangedSignal();
    }

    current = generalTab->CityLineEdit1->text();
    original = (settingEngine.getCities()).at(0);
    QFile file;
    QString XML = ".xml";
    if(original != current)
    {
        settings->setValue(tr("City1"),current);
        file.remove(original+XML);
        emit CityChangedSignal(current);
    }

    current = generalTab->CityLineEdit2->text();
    original =(settingEngine.getCities()).at(1);
    if(current != original)
    {
        settings->setValue(tr("City2"),current);
        file.remove(original+XML);
        emit CityChangedSignal(current);
    }

    current = generalTab->CityLineEdit3->text();
    original = (settingEngine.getCities()).at(2);
    if(current != original)
    {
        settings->setValue(tr("City3"),current);
        file.remove(original+XML);
        emit CityChangedSignal(current);
    }

    current = QString::number(userDefineTab->UpdateFrequenceSpinBox->value());
    original = QString::number(settingEngine.getUpdateFrequence());
    if(current != original)
    {
        settings->setValue(tr("UpdateFrequence"),current);
        emit UpdateFrequencyChangedSignal(current);
    }


    settings->setValue(tr("transparency"),userDefineTab->TransparencySlider->value());


    bool isF = settingEngine.isF();
    original = "c";
    if(isF)
    {
        original = "f";
    }
    current = QObject::tr("c");
    if(userDefineTab->CentigradeRbtn->isChecked())
        current = QObject::tr("f");
    if(current != original)
    {
        settings->setValue(tr("TemperatureType"),current);
        emit TemperatureTypeChangedSignal(current);
    }

    original = settingEngine.getLanguage();
    if(generalTab->english->isChecked())
        current = generalTab->english->text();
    else
        current = QString(QObject::tr("chinese"));
    if(current != original)
    {
        settings->setValue(tr("Language"),current);
        emit LanguageChangedSignal(current);
    }
   // QVariant key("City");
   // this->advanceTab->IP->setText(ReadSetting(key).toString());
    delete settings;
    this->close();

}
//=============================================================================
QVariant TabDialog::ReadSetting(QVariant key)
{
    QSettings *settings = new QSettings("Meteorologist.ini", QSettings::IniFormat);
    QVariant value =settings->value(key.toString(),tr(""));
    delete settings;
    return value;

}
//=============================================================================
void TabDialog::SettingTransparency(int value)
{
    float tempValue = 1.0;
    tempValue = (float)value/100;
    QString transparency = QString::number(tempValue);
    setWindowOpacity(transparency.toFloat());
}
//=============================================================================
GeneralTab::GeneralTab(QWidget *parent)
  :QWidget(parent)
{
    QSettings settings("Meteorologist.ini", QSettings::IniFormat);
    SetCityGroup = new QGroupBox(tr("Location"));
    iTopHBoxLayout = new QVBoxLayout;
    iTopHBoxLayout->setAlignment(Qt::AlignTop);

    iHBoxCityLayout = new QHBoxLayout();

    QLabel *CityLabel1 = new QLabel(tr("City1"));
    CityLineEdit1 = new QLineEdit(tr("ChengDu"));
    CityLineEdit1->setText(settings.value(tr("City1"),tr("ChengDu")).toString());
    CityLineEdit1->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QLabel *CityLabel2 = new QLabel(tr("City2"));
    CityLineEdit2 = new QLineEdit(tr("City2"));
    CityLineEdit2->setText(settings.value(tr("City2"),tr("BeiJing")).toString());
    CityLineEdit2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    QLabel *CityLabel3 = new QLabel(tr("City3"));
    CityLineEdit3 = new QLineEdit(tr("City3"));
    CityLineEdit3->setText(settings.value(tr("City3"),tr("ShangHai")).toString());
    CityLineEdit3->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);

    iGridCityLayout = new QGridLayout();
    iGridCityLayout->addWidget(CityLabel1,0,0,Qt::AlignRight);
    iGridCityLayout->addWidget(CityLabel2,1,0,Qt::AlignRight);
    iGridCityLayout->addWidget(CityLabel3,2,0,Qt::AlignRight);
    iGridCityLayout->addWidget(CityLineEdit1,0,1,Qt::PreferredSize,10,Qt::AlignLeft);
    iGridCityLayout->addWidget(CityLineEdit2,1,1,Qt::AlignLeft);
    iGridCityLayout->addWidget(CityLineEdit3,2,1,Qt::AlignLeft);

    SetCityGroup->setLayout(iGridCityLayout);

    SetLanguageGroup = new QGroupBox(tr("Language"));
    english = new QRadioButton(tr("english"));
    chinese = new QRadioButton(tr("ÖÐÎÄ"));

    iVLanguageLyout = new QVBoxLayout;
    iVLanguageLyout->addWidget(english);
    iVLanguageLyout->addWidget(chinese);
    SetLanguageGroup->setLayout(iVLanguageLyout);
     QString LanguageSelected = settings.value(tr("Language"),tr("english")).toString();
    if(LanguageSelected.compare("english") == 0)
    {
        english->setChecked(true);
    }
    else
    {
        chinese->setChecked(true);
    }

    iTopHBoxLayout->addWidget(SetCityGroup);
    iTopHBoxLayout->addWidget(SetLanguageGroup);

    setLayout(iTopHBoxLayout);

}
GeneralTab::~GeneralTab()
{

    if( english!=NULL )
    {
        delete english;
    }
    delete chinese;
    delete CityLineEdit1;
    delete CityLineEdit2;
    delete CityLineEdit3;
    delete iTopHBoxLayout;
    delete iHBoxCityLayout;
    delete iVLanguageLyout;
    delete iGridCityLayout;
    delete SetCityGroup;
    delete SetLanguageGroup;

}
//=============================================================================
void GeneralTab::Init()
{
     QSettings settings("Meteorologist.ini", QSettings::IniFormat);
     CityLineEdit1->setText(settings.value(tr("City"),tr("ChengDu")).toString());
}
//=============================================================================
UserDefineTab::UserDefineTab(TabDialog *tabDialog, QWidget *parent)
  :QWidget(parent)
{
    QSettings settings("Meteorologist.ini", QSettings::IniFormat);
    MainLayout = new QVBoxLayout;
    DispalItemNumGroup = new QGroupBox(tr("Days displayed"));
    DispalItemNumLayout = new QHBoxLayout;

    DisplayItemNum = new QComboBox;
    DisplayItemNum->addItem(tr("1"));
    DisplayItemNum->addItem(tr("2"));
    DisplayItemNum->addItem(tr("3"));
    DisplayItemNum->addItem(tr("4"));
    DisplayItemNum->addItem(tr("5"));
    QString DisPlayItemNumSelected = settings.value(tr("DaysDisplayed"),tr("3")).toString();
    DisplayItemNum->setCurrentIndex(DisPlayItemNumSelected.toInt()-1);

    QLabel *iDayStr = new QLabel(tr("days"));
    DispalItemNumLayout->addWidget(DisplayItemNum);
    DispalItemNumLayout->addWidget(iDayStr);
    DispalItemNumGroup->setLayout(DispalItemNumLayout);

    CentigradeRbtn = new QRadioButton(tr("¡ãF"));
    DegreeRbtn = new QRadioButton(tr("¡æ"));
    QString TemperatureType = settings.value(tr("TemperatureType"),tr("c")).toString();
    if(TemperatureType.compare(tr("f")) == 0)
    {
        CentigradeRbtn->setChecked(true);
    }
    else
    {
        DegreeRbtn->setChecked(true);
    }
    TemperatureLayout = new QVBoxLayout;
    TemperatureTypeGroup = new QGroupBox(tr("¡ãF/¡æ"));

    UpdateFrequenceSpinBox = new QSpinBox();
    UpdateFrequenceSpinBox->setRange(5,120);
    UpdateFrequenceSpinBox->setSingleStep(5);

    QLabel *UpdateFrequenceStr = new QLabel(tr("Minutes"));
    QString UpdateFrequence = settings.value(tr("UpdateFrequence"),tr("")).toString();
    if(UpdateFrequence.compare(tr("")) == 0)
    {
        UpdateFrequenceSpinBox->setValue(5);
    }
    else
    {
        UpdateFrequenceSpinBox->setValue(UpdateFrequence.toInt());
    }
    UpdateFrequenceLayout = new QHBoxLayout;
    UpdateFrequenceLayout->addWidget(UpdateFrequenceSpinBox);
    UpdateFrequenceLayout->addWidget(UpdateFrequenceStr);
    UpdateFrequenceGroup = new QGroupBox(tr("Update Frequence"));
    UpdateFrequenceGroup->setLayout(UpdateFrequenceLayout);

    TemperatureLayout->addWidget(CentigradeRbtn);
    TemperatureLayout->addWidget(DegreeRbtn);
    TemperatureTypeGroup->setLayout(TemperatureLayout);

    TransparencyGroup = new QGroupBox("Transparency");
    TransparencySlider = new QSlider(Qt::Horizontal);
    TransparencyLayout = new QVBoxLayout;
    TransparencyLabel = new QLabel(tr("transparency: "));
    TransparencySlider->setRange(50,100);
    TransparencySlider->setSingleStep(1);
    QString transparency = settings.value(tr("transparency"),tr("100")).toString();

    QString temp(tr("transparency: "));
    temp.append(QString::number(transparency.toInt()));
    temp.append(tr("%"));
    TransparencyLabel->setText(temp);
    TransparencySlider->setValue(transparency.toInt());
    tabDialog->SettingTransparency(transparency.toInt());


    TransparencyLayout->addWidget(TransparencyLabel,0,Qt::AlignCenter);
    TransparencyLayout->addWidget(TransparencySlider);
    TransparencyGroup->setLayout(TransparencyLayout);
    connect(TransparencySlider,SIGNAL(sliderMoved(int)),this,SLOT(UpdateTransparencyLabel(int)));
    connect(TransparencySlider,SIGNAL(sliderMoved(int)),tabDialog,SLOT(SettingTransparency(int)));

    MainLayout->addWidget(DispalItemNumGroup,20);
    MainLayout->addWidget(TemperatureTypeGroup,20);
    MainLayout->addWidget(UpdateFrequenceGroup,20);
    MainLayout->addWidget(TransparencyGroup,20);

    setLayout(MainLayout);
}
UserDefineTab::~UserDefineTab()
{
    delete MainLayout;
    delete DisplayItemNum;

    delete DispalItemNumLayout;

    delete CentigradeRbtn;
    delete DegreeRbtn;
    delete TemperatureLayout;
    delete UpdateFrequenceSpinBox;
    delete UpdateFrequenceLayout;
    delete TransparencySlider;
    delete TransparencyLayout;
    delete TransparencyLabel;
    delete DispalItemNumGroup;
    delete TemperatureTypeGroup;
    delete TransparencyGroup;
    delete UpdateFrequenceGroup;
}
//=============================================================================
void UserDefineTab::UpdateTransparencyLabel(int value)
{
    QString valueLast("transparency: ");
    QString valueStr = QString::number( value );
    valueLast += valueStr;
    valueLast += "%";
    TransparencyLabel->setText(valueLast);
}
//=============================================================================
void UserDefineTab::Init()
{}
//=============================================================================

AdvanceTab::AdvanceTab(QWidget *parent):QWidget(parent)
{
     QSettings settings("Meteorologist.ini", QSettings::IniFormat);
    MainLayout = new QVBoxLayout;
    BootSettingLayout = new QVBoxLayout;
    BootSettingGruop = new QGroupBox(tr("Start Up"));
    AutoBoot = new QCheckBox(tr("Run Automaticlly After The Computer Started"));
    QString AutoBootSelected = settings.value(tr("AutoBoot"),tr("0")).toString();

    if(AutoBootSelected.compare(tr("false")) != 0)
    {
        AutoBoot->setChecked(true);
    }
    BootSettingLayout->addWidget(AutoBoot);
    BootSettingGruop->setLayout(BootSettingLayout);

    SetProxyGroup = new QGroupBox(tr("Proxy"));
    SetProxyLayout = new QGridLayout;
    QLabel *ProxyTypeStr = new QLabel(tr("ProxyType:"));
    ProxyTypeComboBox = new QComboBox;
    ProxyTypeComboBox->addItem(tr("Disabled"));
    ProxyTypeComboBox->addItem(tr("HTTP"));
    ProxyTypeComboBox->addItem(tr("SOCKS5"));
    ProxyTypeComboBox->addItem(tr("Use Browser Proxy"));
    ProxyTypeComboBox->setCurrentIndex(settings.value(tr("ProxIpStatus"),tr("0")).toInt());

    QLabel *IPStr = new QLabel(tr("IP£º"));
    IP= new QLineEdit;
    QString ProxyIpSelected = settings.value(tr("ProxyIp")).toString();
    IP->setText(ProxyIpSelected);
    QString rxStringTemp = "((1[0-9]?[0-9]?)|(2[0-4][0-9]?)|(3[0-9]?)|(4[0-9]?)|(5[0-9]?)|(6[0-9]?)|(7[0-9]?)|(8[0-9]?)|(9[0-9]?)|(25[0-4]?))";
    QString rxString =rxStringTemp + "\\." + rxStringTemp + "\\." + rxStringTemp + "\\." + rxStringTemp;
    QRegExp rx(rxString);
    QValidator *ipValidator = new QRegExpValidator(rx, this);
    IP->setValidator(ipValidator);

    QLabel *PORTStr = new QLabel(tr("PORT:"));
    PORT= new QLineEdit;
    QString PortSelected = settings.value((tr("ProxyPort"))).toString();
    PORT->setText(PortSelected);

    QRegExp PortExp("^\\d\\d\\d\\d?$");
    QValidator *portValidator = new QRegExpValidator(PortExp,this);
    PORT->setValidator(portValidator);

    QLabel *UserStr = new QLabel(tr("User:"));
    UserLineEdit = new QLineEdit;
    UserLineEdit->setText(settings.value(tr("ProxyIp")).toString());
    QLabel *PassWordStr = new QLabel(tr("Password:"));
    PasswordLineEdit = new QLineEdit;
    PasswordLineEdit->setEchoMode(QLineEdit::Password);
    PasswordLineEdit->setText(settings.value(tr("ProxyPort")).toString());
    QLabel *DomainStr = new QLabel(tr("Domain:"));
    DomainLineEdit = new QLineEdit;
    DomainLineEdit->setText(settings.value(tr("Domain")).toString());

    TestProxyBtn = new QPushButton(tr("Test"));

    QString ProxyStatusSelected = settings.value(tr("ProxIpStatus"),tr("0")).toString();
    if(ProxyStatusSelected.compare(tr("0")) != 0)
    {
        IP->setEnabled(true);;
        PORT->setEnabled(true);
        UserLineEdit->setEnabled(true);
        PasswordLineEdit->setEnabled(true);
        DomainLineEdit->setEnabled(true);

    }
    else
    {
        IP->setDisabled(true);
        PORT->setDisabled(true);
        UserLineEdit->setDisabled(true);
        PasswordLineEdit->setDisabled(true);
        DomainLineEdit->setDisabled(true);
    }


    connect(ProxyTypeComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ChangeIpPortStatus()));

    SetProxyLayout->addWidget(ProxyTypeStr,0,0,Qt::AlignLeft);
    SetProxyLayout->addWidget(IPStr,0,1,Qt::AlignLeft);
    SetProxyLayout->addWidget(PORTStr,0,2,Qt::AlignLeft);
    SetProxyLayout->addWidget(UserStr,2,0,Qt::AlignLeft);
    SetProxyLayout->addWidget(PassWordStr,2,1,Qt::AlignLeft);
    SetProxyLayout->addWidget(DomainStr,2,2,Qt::AlignLeft);

    SetProxyLayout->addWidget(ProxyTypeComboBox,1,0,Qt::AlignLeft);
    SetProxyLayout->addWidget(IP,1,1,Qt::AlignLeft);
    SetProxyLayout->addWidget(PORT,1,2,Qt::AlignLeft);
    SetProxyLayout->addWidget(UserLineEdit,3,0,Qt::AlignLeft);
    SetProxyLayout->addWidget(PasswordLineEdit,3,1,Qt::AlignLeft);
    SetProxyLayout->addWidget(DomainLineEdit,3,2,Qt::AlignLeft);

    SetProxyLayout->addWidget(TestProxyBtn,4,2,Qt::AlignRight);
    SetProxyGroup->setLayout(SetProxyLayout);

    ServerSelectLayout = new QHBoxLayout;
    ServerSelectGroup = new QGroupBox(tr("ServerSelect"));
    ServerSelectComboBox =new QComboBox;
    QLabel *SeverSelectLabel = new QLabel(tr("Server:"));
    ServerSelectComboBox->addItem(tr("Google"));
    ServerSelectComboBox->addItem(tr("MSN"));
    QString ServerSelected = settings.value(tr("ServerIndex"),tr("1")).toString();
    ServerSelectComboBox->setCurrentIndex(ServerSelected.toInt());

    ServerSelectLayout->addWidget(SeverSelectLabel);
    ServerSelectLayout->addWidget(ServerSelectComboBox,100,Qt::AlignLeft);
    ServerSelectGroup->setLayout(ServerSelectLayout);

    MainLayout->addWidget(BootSettingGruop);
    MainLayout->addWidget(SetProxyGroup);
    MainLayout->addWidget(ServerSelectGroup);

    setLayout(MainLayout);


}
AdvanceTab::~AdvanceTab()
{
    delete MainLayout;
    delete BootSettingLayout;
    delete ServerSelectLayout;
    delete BootSettingGruop;
    delete ServerSelectGroup;
    delete IP;
    delete PORT;
    delete SetProxyGroup;
}
//=============================================================================
void AdvanceTab::Init()
{}
//=============================================================================

void AdvanceTab::ChangeIpPortStatus()
{
    if(ProxyTypeComboBox->currentIndex() != 0)
    {
        IP->setEnabled(true);
        PORT->setEnabled(true);
        UserLineEdit->setEnabled(true);
        PasswordLineEdit->setEnabled(true);
        DomainLineEdit->setEnabled(true);
    }
    else
    {
        IP->setDisabled(true);
        PORT->setDisabled(true);
        UserLineEdit->setDisabled(true);
        PasswordLineEdit->setDisabled(true);
        DomainLineEdit->setDisabled(true);
    }
}

