#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget(parent)

{
    ui_setting->setupUi(this);

    QString lastBackground = settings.value("Setting_backgroundImage_StyleSheet").toString();
    if (!lastBackground.isEmpty()) {
        qDebug() << lastBackground;
        ui_setting->label->setStyleSheet(lastBackground);
    }


    if(settings.value("bgm").toString() == "on"){

        ui_setting->bgm->setChecked(true);
    }else{
        ui_setting->bgm->setChecked(false);
    }

    if(settings.value("effect").toString() == "on"){

        ui_setting->effect->setChecked(true);
    }else{
        ui_setting->effect->setChecked(false);
    }

    if( settings.value("CountDown").toBool()){
        ui_setting->CountDown->setChecked(true);
        player_bgm->loops();
    }else{
        ui_setting->CountDown->setChecked(false);
    }

}

SettingWidget::~SettingWidget()
{
    delete ui_setting;
}

void SettingWidget::on_Back_clicked()
{
    this->close();
}




void SettingWidget::on_Setting_Background_Path_clicked()
{
    // 打开文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");

    if (!fileName.isEmpty()) {
        QString styleSheet = QString("background-image: url(%1);").arg(fileName);
        ui_setting->label->setStyleSheet(styleSheet);
        // 保存背景图片路径
        QSettings settings("Kurihara_Mio", "Checkers_Game");
        settings.setValue("Setting_backgroundImage_StyleSheet", styleSheet);
    }
}


void SettingWidget::on_BGM_Path_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Audio", "", "Audios (*.mp3)");
    if (!fileName.isEmpty()) {
        BGM_Path = fileName;
        settings.setValue("BGM_Path", QUrl(BGM_Path));
        QUrl bgm_path = settings.value("BGM_Path").toUrl();
        if(!bgm_path.isEmpty()){
            player_bgm->setSource(bgm_path);
        }else{
            player_bgm->setSource(QUrl("qrc:/media/assets/bgm.mp3"));
        }
        if(settings.value("bgm").toString() == "on"){
            player_bgm->loops();
            player_bgm->play();
        }
        player_bgm->play();
    }
}


void SettingWidget::on_effect_clicked(bool checked)
{
    if(checked){
        settings.setValue("effect","on");
    }else{
        settings.setValue("effect","off");
    }
}


void SettingWidget::on_bgm_clicked(bool checked)
{
    if(checked){
        settings.setValue("bgm","on");
        player_bgm->loops();
        player_bgm->play();
    }else{
        settings.setValue("bgm","off");
        player_bgm->pause();
    }

}


void SettingWidget::on_menu_background_Path_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        ui_mainwindow->label->setStyleSheet(QString("background-image: url(%1)；").arg(fileName));
        Menu_Background_Path = fileName;
        settings.setValue("Menu_Background_Path", Menu_Background_Path);
    }
}


void SettingWidget::on_Board_Background_Path_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Board_Background_Path = fileName;
        settings.setValue("Board_Background_Path", Board_Background_Path);
    }
}



void SettingWidget::on_Red_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Red_Image_Path = fileName;
        settings.setValue("red_Image_Path", Red_Image_Path);
    }
}


void SettingWidget::on_Purple_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Purple_Image_Path = fileName;
        settings.setValue("purple_Image_Path", Purple_Image_Path);
    }
}


void SettingWidget::on_Blue_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Blue_Image_Path = fileName;
        settings.setValue("blue_Image_Path", Blue_Image_Path);
    }
}


void SettingWidget::on_Green_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Green_Image_Path = fileName;
        settings.setValue("green_Image_Path", Green_Image_Path);
    }
}


void SettingWidget::on_Yellow_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Yellow_Image_Path = fileName;
        settings.setValue("yellow_Image_Path", Yellow_Image_Path);
    }
}


void SettingWidget::on_Orange_Image_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Orange_Image_Path = fileName;
        settings.setValue("orange_Image_Path", Orange_Image_Path);
    }
}




void SettingWidget::on_red_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("red_Name",text);
    }
}


void SettingWidget::on_purple_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("purple_Name",text);
    }
}


void SettingWidget::on_blue_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("blue_Name",text);
    }
}




void SettingWidget::on_green_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("green_Name",text);
    }
}


void SettingWidget::on_yellow_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("yellow_Name",text);
    }
}


void SettingWidget::on_orange_name_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请输入名字:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("orange_Name",text);
    }
}

void SettingWidget::on_Change_Word_Color_clicked()
{
    QString stylesheet;
    QString text = QInputDialog::getText(this, "输入文本", "获取rgba:https://www.gongjumi.com/generator/colorPicker\n请输入rgb（格式为：0,0,0)", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("word_color_rgb",text);
        QString rgb = settings.value("word_color_rgb").toString();
        if(!rgb.isEmpty()){
            stylesheet = QString("color: rgb(%1);").arg(rgb);
        }
        settings.setValue("word_stylesheet",stylesheet);
    }

    for(int i = 0;i<=16;i++){
        QLabel* label = findChild<QLabel*>(QString("label_%1").arg(i));

        if (label) {
            QString last_stylesheet = settings.value("word_stylesheet").toString();
            if (!last_stylesheet.isEmpty()) {
                label->setStyleSheet(last_stylesheet);
            } else {
                label->setStyleSheet("color: rgb(0, 0, 0);");
            }
        }

    }

}



void SettingWidget::on_Winner_Background_Path_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Select Image", "", "Images (*.png *.xpm *.jpg)");
    if (!fileName.isEmpty()) {
        Winner_Background_Path = fileName;
        settings.setValue("Winner_Background_Path", Winner_Background_Path);
    }

}


void SettingWidget::on_CountDown_set_clicked()
{
    QString text = QInputDialog::getText(this, "输入文本", "请设定限时时间（秒）:", QLineEdit::Normal);
    if(!text.isEmpty()){
        settings.setValue("CountDown_set",text.toInt());
    }
}


void SettingWidget::on_CountDown_clicked(bool checked)
{
    if(checked){
        settings.setValue("CountDown",true);
    }else{
        settings.setValue("CountDown",false);
    }
}


void SettingWidget::on_clear_clicked()
{
    ClearDialog* cleardialog = new ClearDialog(this);
    cleardialog->setWindowIconText("提醒");
    cleardialog->show();
}

