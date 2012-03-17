#ifndef __TABDLG_H__
#define __TABDLG_H__

#include <QDialog>
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "QComboBox"
#include "QGroupBox"
#include "QRadioButton"
#include "QCheckBox"
#include "QSettings"
#include "QtGui"

class QWidget;
class QFileInfo;
class QTabWidget;
class QDialogButtonBox;


class GeneralTab : public QWidget
{
        Q_OBJECT

public:
        GeneralTab(QWidget *parent = 0);
        ~GeneralTab();
        void Init();

public:
        QVBoxLayout* iTopHBoxLayout;
        QHBoxLayout* iHBoxCityLayout;
        QVBoxLayout* iVLanguageLyout;
        QGridLayout* iGridCityLayout;
        QGroupBox* SetCityGroup;
        QGroupBox* SetPoxyGroup;
        QGroupBox* SetLanguageGroup;
        QGroupBox* UserDefineGroup;
        QComboBox* province;
        QComboBox* city;
        QLineEdit* IP;
        QLineEdit* PORT;
        QRadioButton* english;
        QRadioButton* chinese;
        QLineEdit* CityLineEdit1;
        QLineEdit* CityLineEdit2;
        QLineEdit* CityLineEdit3;



};

class TabDialog;
class UserDefineTab : public QWidget
{
        Q_OBJECT

public:
        UserDefineTab(TabDialog *tabDialog, QWidget *parent = 0);
        ~UserDefineTab();
        void Init();
        QVBoxLayout *MainLayout;
        QComboBox *DisplayItemNum;
        QGroupBox *DispalItemNumGroup;
        QHBoxLayout *DispalItemNumLayout;
        QGroupBox *TemperatureTypeGroup;
        QRadioButton *CentigradeRbtn;
        QRadioButton *DegreeRbtn;
        QVBoxLayout *TemperatureLayout;
        QSpinBox *UpdateFrequenceSpinBox;
        QGroupBox *UpdateFrequenceGroup;
        QHBoxLayout *UpdateFrequenceLayout;
        QSlider *TransparencySlider;
        QGroupBox *TransparencyGroup;
        QVBoxLayout *TransparencyLayout;
        QLabel *TransparencyLabel;
    public slots:
        void UpdateTransparencyLabel(int value);
};

class AdvanceTab : public QWidget
{
        Q_OBJECT

public:
        AdvanceTab(QWidget *parent = 0);
        ~AdvanceTab();
        void Init();
        QVBoxLayout *MainLayout;
        QVBoxLayout *BootSettingLayout;
        QHBoxLayout *ServerSelectLayout;
        QGroupBox *BootSettingGruop;
        QGroupBox *ServerSelectGroup;
        QCheckBox *AutoBoot;
        QCheckBox *ProxyStatus ;
        QLineEdit *IP;
        QLineEdit *PORT;
        QGroupBox *SetProxyGroup;
        QComboBox *ServerSelectComboBox;
        QComboBox *ProxyTypeComboBox;
        QLineEdit *UserLineEdit;
        QLineEdit *PasswordLineEdit;
        QLineEdit *DomainLineEdit;
        QGridLayout *SetProxyLayout;
        QPushButton *TestProxyBtn;
    public slots:
        void ChangeIpPortStatus();

};


class TabDialog : public QDialog
{
    Q_OBJECT
public:
  TabDialog();
  TabDialog(QWidget *parent);
  void SettingBackGround();
private:
  QTabWidget *tabWidget;
  QDialogButtonBox *buttonBox;
  QPoint lastPos;
  QPoint Pos;
public:
  GeneralTab *generalTab;
  AdvanceTab *advanceTab;
  UserDefineTab *userDefineTab;
  QPushButton *SaveButton;
public:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

public slots:
    QVariant ReadSetting(QVariant key);
    void SettingTransparency(int value);
    void WriteSetting();
    void autoRun( bool isAutoRun );
signals:
    void ProxyChangedSignal();
    void ServerChangedSignal(QString server);
    void AutoRunStatusChangedSignal(bool autoRun);
    void DisplayedDaysChangedSignal();
    void CityChangedSignal(QString city);
    void UpdateFrequencyChangedSignal(QString updateFrequency);
    void TemperatureTypeChangedSignal(QString temperatureType);
    void LanguageChangedSignal(QString language);

};


#endif // __TABDLG_H__
