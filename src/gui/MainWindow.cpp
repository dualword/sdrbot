/*
 * Copyright (C) 2012 Alexander Busorgin
 *
 *	This file is part of sdrBot.
 *
 *	sdrBot is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	sdrBot is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with sdrBot.  If not, see <http://www.gnu.org/licenses/>.
 *
*/

#include "gui/MainWindow.h"

using namespace std;

MainWindow::MainWindow(Context *ctx, QTranslator *translator)
{

	step = 0;
	isHidden = false;
	this->translator = translator;
	this->ctx = ctx;
	receiver = ctx->getReceiver();

	buffer = new QString("");
    setWindowTitle(QString::fromStdString("sdrBot"));
    setFixedSize(350, 350);

    createTrayIcon(); //systray

    statusBar();  //statusbar
    statusBar()->setSizeGripEnabled(false);
    mStateRcv = new QLabel;
    statusBar()->addPermanentWidget(mStateRcv);

    QAction *quit = new QAction("&Quit", this);

    QMenu *menu = menuBar()->addMenu( tr("&File") );
    settingsAction = new QAction(tr("Settings"), this);
    menu->addAction(settingsAction);

    menu->addSeparator();
    menu->addAction(quit);
    QObject::connect(quit, SIGNAL(triggered()), this, SLOT(quit1()));

    QMenu *aboutMenu = menuBar()->addMenu(tr("&Help"));
//    QAction *helpAction = new QAction(tr("Content"), this);
//    aboutMenu->addAction(helpAction);
    //aboutMenu->addSeparator();

    aboutAction = new QAction(tr("A&bout"), this);
    aboutMenu->addAction(aboutAction);

    QToolBar *toolbar;
    toolbar = addToolBar( tr("File") );

    btnConnect = new QAction(tr("C"), this);
    toolbar->addAction(btnConnect); //QIcon(quitpix),

    //toolbar->addSeparator();
	btnTune = new QAction(tr("T"), this);
	btnTune->setToolTip("Tune");
	//toolbar->addAction(btnTune);

    toolbar->setMovable(false);

    QVBoxLayout *lay = new QVBoxLayout;
    //lay->setAlignment(Qt::AlignRight);

    //display
    QGridLayout *displaygrid = new QGridLayout;
    display = new QLineEdit;
    display->setReadOnly(true);
    //display->setMaximumWidth(0);
    //display->setText("0000.0000");
//    txt->setMaxLength(txt->maxLength());
//    txt->clear();
    display->setAlignment(Qt::AlignRight);
    displaygrid->addWidget(display,0,0);

    lblMhz = new QLabel("MHz");
    displaygrid->addWidget(lblMhz,0,1);

    progress = new QProgressBar();
    progress->setMinimum(0);
    progress->setMaximum(255);
    displaygrid->addWidget(progress,0,2);

    lblLvl = new QLabel("000");
    lblLvl->setMinimumWidth(25);
    lblLvl->setMaximumWidth(25);
    displaygrid->addWidget(lblLvl,0,3);

    //buttons

    //    	WFM(0),NFM(1),AM(2),USB(3),LSB(4),CW(5),SFM(6),WAM(7),NAM(8);
    modeBox = new QComboBox;
    modeBox->addItem("WFM",0);
    modeBox->addItem("NFM",1);
    modeBox->addItem("AM",2);
    modeBox->addItem("USB",3);
    modeBox->addItem("LSB",4);
    modeBox->addItem("CW",5);
    modeBox->addItem("SFM",6);
    modeBox->addItem("WAM",7);
    modeBox->addItem("NAM",8);
    modeBox->setToolTip("Mode");

    attBox= new QComboBox;
    attBox->addItem("OFF",0);
    attBox->addItem("ON",1);
    attBox->setToolTip("Attenuator");

    stepBox = new QComboBox;
    stepBox->addItem("50Hz",0.00005);
    stepBox->addItem("100Hz",0.0001);
    stepBox->addItem("200Hz",0.0002);
    stepBox->addItem("500Hz",0.0005);
    stepBox->addItem("1kHz",0.001);
    stepBox->addItem("2kHz",0.002);
    stepBox->addItem("5kHz",0.005);
    stepBox->addItem("6.25kHz",0.00625);
    //stepBox->addItem("8.33kHz",0.00833);
    stepBox->addItem("9kHz",0.009);
    stepBox->addItem("10kHz",0.01);
    stepBox->addItem("12.50kHz",0.0125);
    stepBox->addItem("20kHz",0.02);
    stepBox->addItem("25kHz",0.025);
    stepBox->addItem("30kHz",0.033);
    stepBox->addItem("50kHz",0.05);
    stepBox->addItem("100kHz",0.1);

    stepBox->setToolTip("Step");


    QGridLayout *grid = new QGridLayout;

    btn1 = createButton(tr("1"), SLOT(buttonClicked()));
    btn2 = createButton(tr("2"), SLOT(buttonClicked()));
    btn3 = createButton(tr("3"), SLOT(buttonClicked()));
    grid->addWidget(modeBox,0,0);
    grid->addWidget(btn1,0,1);
    grid->addWidget(btn2,0,2);
    grid->addWidget(btn3,0,3);

    btn4 = createButton(tr("4"), SLOT(buttonClicked()));
    btn5 = createButton(tr("5"), SLOT(buttonClicked()));
    btn6 = createButton(tr("6"), SLOT(buttonClicked()));
    grid->addWidget(attBox,1,0);
    grid->addWidget(btn4,1,1);
    grid->addWidget(btn5,1,2);
    grid->addWidget(btn6,1,3);

    btn7 = createButton(tr("7"), SLOT(buttonClicked()));
    btn8 = createButton(tr("8"), SLOT(buttonClicked()));
    btn9 = createButton(tr("9"), SLOT(buttonClicked()));
    grid->addWidget(stepBox,2,0);
    grid->addWidget(btn7,2,1);
    grid->addWidget(btn8,2,2);
    grid->addWidget(btn9,2,3);

    btnc = createButton(tr("&Clear"), SLOT(buttonClicked()));
    btnd = createButton(tr("."), SLOT(buttonClicked()));
    btnz = createButton(tr("0"), SLOT(buttonClicked()));
    btne = createButton(tr("Enter"), SLOT(buttonClicked()));

    grid->addWidget(btnc,3,0);
    grid->addWidget(btnd,3,1);
    grid->addWidget(btnz,3,2);
    grid->addWidget(btne,3,3);

    //sliders
    lblAudio = new QLabel("Audio");
    lblLevel = new QLabel("Level");

    QGridLayout *sliderGrid = new QGridLayout;
	audioSquelch = new QSlider(Qt::Horizontal, this);
	audioSquelch->setMinimum(0);
	audioSquelch->setMaximum(255);
	audioSquelch->setToolTip("Squelch");
	levelSquelch = new QSlider(Qt::Horizontal, this);
	levelSquelch->setMinimum(0);
	levelSquelch->setMaximum(255);
	levelSquelch->setToolTip("Squelch");

	lblSqA = new QLabel("");
	lblSqA->setMinimumWidth(25);
	lblSqA->setMaximumWidth(25);

	lblSqL = new QLabel("");
	lblSqL->setMinimumWidth(25);
	lblSqL->setMaximumWidth(25);

	sqAleft = new QPushButton("<");
	sqAleft->setMinimumWidth(20);
	sqAleft->setMaximumWidth(20);
	sqAright = new QPushButton(">");
	sqAright->setMinimumWidth(20);
	sqAright->setMaximumWidth(20);
	sqLleft = new QPushButton("<");
	sqLleft->setMinimumWidth(20);
	sqLleft->setMaximumWidth(20);
	sqLright = new QPushButton(">");
	sqLright->setMinimumWidth(20);
	sqLright->setMaximumWidth(20);

	sliderGrid->addWidget(lblAudio,0,0);
	sliderGrid->addWidget(sqAleft,0,1);
	sliderGrid->addWidget(audioSquelch,0,2);
	sliderGrid->addWidget(sqAright,0,3);
	sliderGrid->addWidget(lblSqA,0,4);

	sliderGrid->addWidget(lblLevel,1,0);
	sliderGrid->addWidget(sqLleft,1,1);
	sliderGrid->addWidget(levelSquelch,1,2);
	sliderGrid->addWidget(sqLright,1,3);
	sliderGrid->addWidget(lblSqL,1,4);

    lay->addLayout(displaygrid);
    lay->addLayout(grid);
    lay->addLayout(sliderGrid);

    QWidget *w = new QWidget;
    w->setLayout(lay);
    setCentralWidget(w);

    //center the window
    QDesktopWidget *desktop = QApplication::desktop();
    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;
    screenWidth = desktop->width();
    screenHeight = desktop->height();
    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();
    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;
    move ( x, y );

    disableControls();
    setSlots();

	tuneForm = new TuneForm (this);

	//event filters
	installEventFilter(this);
	updateEventFilters(this);

	changeStep();
}

MainWindow::~MainWindow()
{
	if(buffer) delete buffer;
	if (tuneForm) delete tuneForm;

}

void MainWindow::updateEventFilters( QObject* obj )
{
   foreach( QObject * obj, obj->children() ) {
      obj->installEventFilter( this );
      updateEventFilters( obj );
   }
}


void MainWindow::quit1()
{
	receiver->disconnect();
	ctx->close();
	qApp->quit();

}

QPushButton *MainWindow::createButton(const QString &text, const char *member)
 {
	QPushButton *button = new QPushButton(text);
	button->installEventFilter(this);
     connect(button, SIGNAL(clicked()), this, member);
     return button;
 }

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if (event->type() == QEvent::KeyPress ){
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if(receiver->getStatus() == Receiver::Status::on){
			switch (keyEvent->key()) {
			case (Qt::Key_Left): scrollLeft() ; return true;
			case (Qt::Key_Right): scrollRight(); return true;
			case (Qt::Key_Up): scrollUp(); return true;
			case (Qt::Key_Down): scrollDown(); return true;
			default:
			    return false;
			}
		}
		return false;
	}else if (event->type() == QEvent::KeyRelease){
		QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
		if(receiver->getStatus() == Receiver::Status::on){
			switch (keyEvent->key()) {
			case (Qt::Key_Left): ; return true;
			case (Qt::Key_Right): ; return true;
			case (Qt::Key_Up): ; return true;
			case (Qt::Key_Down): ; return true;
			default:
			    return false;
			}
		}
	}else{
		return QObject::eventFilter(obj, event);
	}
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
	case (Qt::Key_Enter): btne->click(); break;
	case (Qt::Key_Return): btne->click(); break;
	case (Qt::Key_Escape): btnc->click(); break;
	case (Qt::Key_Period): btnd->click(); break;
	case (Qt::Key_0): btnz->click(); break;
	case (Qt::Key_1): btn1->click(); break;
	case (Qt::Key_2): btn2->click(); break;
	case (Qt::Key_3): btn3->click(); break;
	case (Qt::Key_4): btn4->click(); break;
	case (Qt::Key_5): btn5->click(); break;
	case (Qt::Key_6): btn6->click(); break;
	case (Qt::Key_7): btn7->click(); break;
	case (Qt::Key_8): btn8->click(); break;
	case (Qt::Key_9): btn9->click(); break;
	default:
	    QWidget::keyPressEvent(event);
	}
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{

}

void MainWindow::scrollLeft()
{
	try {
		receiver->scrollLeft(step);
	} catch (exception& e) {
		//noop
	}
}

void MainWindow::scrollRight()
{
	try {
		receiver->scrollRight(step);
	} catch (exception& e) {
		//noop
	}
}

void MainWindow::scrollUp()
{
	int idx = stepBox->currentIndex();
	int max = stepBox->count();
	if(idx >= max-1) return;
	stepBox->setCurrentIndex( idx+1);
	step = stepBox->itemData(stepBox->currentIndex()).toDouble();
}

void MainWindow::scrollDown()
{
	int idx = stepBox->currentIndex();
	if(idx <= 0) return;
	stepBox->setCurrentIndex( idx-1);
	step = stepBox->itemData(stepBox->currentIndex()).toDouble();
}



void MainWindow::buttonClicked()
 {

	QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
	QString name =  clickedButton->text();

    if( (name == "Enter") & (buffer->length() > 0)){

    	try {
        	double d = buffer->toDouble();
        	Frequency f(d);
        	receiver->setFrequency(f);
    		buffer->clear();
		} catch (exception e) {
			//noop
		}

		return;
    }else if(name == "&Clear"){
    	display->setText("");
    	try {
        	receiver->getFrequency();
		} catch (exception e) {
			//noop
		}
		buffer->clear();
		return;
    }else if((buffer->length() >= 9) && !(name=="Enter")){
		return; //max length
	}else if(name=="." && buffer->count(".")>0){
		return; //cant be 2 .'s
	}else if(name=="." && (buffer->length() <= 0)){
		return; //1st char cannt be .
	}else if(name=="Enter" && (buffer->length() <= 0)){
		return; //1st char cannt be Enter
	}else if ( (buffer->length() == 4) & (buffer->indexOf(".") <= 0) & !(name==".") ){
		return; //no more than 4 digits before .
	}else if ( buffer->indexOf(".") > 0 && buffer->length() - buffer->indexOf(".") >4  ){
		return; //no more than 4 digits after .
	}

    	buffer->append(name);
    	display->setText(">"+buffer->toLower());
}

void MainWindow::connectPort()
{
	try {
		if( this->receiver->getStatus() == Receiver::off){
			receiver->connect();
		}else{
			receiver->disconnect();
		}
	} catch (exception e) {
		//noop
	}
}

void MainWindow::onConnect(){
	settingsAction->setEnabled(false);
	enableControls();

}
void MainWindow::onDisconnect(){
	settingsAction->setEnabled(true);
	disableControls();
}

void MainWindow::onFreqChange(const double &d)
{
	display->setText(QString::fromStdString(receiver->doubletostring(d,5)));
}

void MainWindow::onLevelChange(int level)
{
	progress->setValue(level);
	QString str;
	str.setNum(level);
	lblLvl->setText(str);
}

void MainWindow::onModeChange(int mode)
{
	modeBox->setCurrentIndex(mode);
}

void MainWindow::onAttChange(int att)
{
	attBox->setCurrentIndex(att);
}


void MainWindow::changeMode()
{
	try {
		receiver->setMode(modeBox->itemData(modeBox->currentIndex()).toInt());
	} catch (exception& e) {
		//noop
	}
}

void MainWindow::changeAtt()
{
	try {
		receiver->setAtt(attBox->itemData(attBox->currentIndex()).toInt());
	} catch (exception& e) {
		//noop
	}
}

void MainWindow::changeStep()
{
	step = stepBox->itemData(stepBox->currentIndex()).toDouble();
}

void MainWindow::showAboutForm()
{
	string str = "sdrBot "+ version +" <br>";
	str += "License: GPL v3 <br/>";
	str += "<a href='http://sdrbot.org'>www.sdrbot.org</a> <br/>" ;
	str += "&copy;2012 Alexander Busorgin <br/>" ;

	//str += ""+((ctx->uptime()/60) + " min.");

	QMessageBox::about(this, tr("About"), QString::fromStdString(str) );
}

void MainWindow::showSettingForm()
{
	SettingForm *form = new SettingForm(this, translator, ctx);
	form->exec();
	delete form;
}

void MainWindow::disableControls()
{
	btnConnect->setText("C");
	btnConnect->setToolTip("Connect.");
	//statusBar()->showMessage(tr("Disconnected."));
    mStateRcv->setText(tr("Disconnected."));
	modeBox->setEnabled(false);
	attBox->setEnabled(false);
	stepBox->setEnabled(false);
	display->setText("");
	btne->setEnabled(false);
	btnc->setEnabled(false);
	btnd->setEnabled(false);
	btnz->setEnabled(false);
	btn1->setEnabled(false);
	btn2->setEnabled(false);
	btn3->setEnabled(false);
	btn4->setEnabled(false);
	btn5->setEnabled(false);
	btn6->setEnabled(false);
	btn7->setEnabled(false);
	btn8->setEnabled(false);
	btn9->setEnabled(false);
	audioSquelch->setValue(0);
	audioSquelch->setEnabled(false);
	levelSquelch->setValue(0);
	levelSquelch->setEnabled(false);
	progress->reset();
	lblLvl->setText("");
	lblSqL->setText("OFF");
	lblSqA->setText("OFF");
	sqAleft->setEnabled(false);
	sqAright->setEnabled(false);
	sqLleft->setEnabled(false);
	sqLright->setEnabled(false);

}
void MainWindow::enableControls()
{
	btnConnect->setText("D");
	btnConnect->setToolTip("Disconnect.");
	//statusBar()->showMessage(tr("Connected."));

	//add port, receiver name
	QString rname = QString::fromStdString(receiver->getName());
	QString pname = QString::fromStdString(receiver->getPort()->getName());
    mStateRcv->setText( rname +"@"+ pname );
	modeBox->setEnabled(true);
	attBox->setEnabled(true);
	stepBox->setEnabled(true);
	btne->setEnabled(true);
	btnc->setEnabled(true);
	btnd->setEnabled(true);
	btnz->setEnabled(true);
	btn1->setEnabled(true);
	btn2->setEnabled(true);
	btn3->setEnabled(true);
	btn4->setEnabled(true);
	btn5->setEnabled(true);
	btn6->setEnabled(true);
	btn7->setEnabled(true);
	btn8->setEnabled(true);
	btn9->setEnabled(true);
	audioSquelch->setEnabled(true);
	levelSquelch->setEnabled(true);
	sqAleft->setEnabled(true);
	sqAright->setEnabled(true);
	sqLleft->setEnabled(true);
	sqLright->setEnabled(true);
}

//systray
void MainWindow::createTrayIcon()
{

	QIcon icon(":images/tray-icon.svg");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("sdrBot");


    connect(
            trayIcon,
            SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this,
            SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason))
           );
}

void MainWindow::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::Trigger){
    	trayIcon->hide();
        this->show();
        isHidden = false;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	trayIcon->show();
    isHidden = true;
	hide();
    event->ignore();
}

void MainWindow::onError(std::string& str)
{
	//cout << "onerror:" << str << endl;
	if(!isHidden)
		QMessageBox::critical(0, "Error", QString::fromStdString(str));
}



void MainWindow::onReceiverChange(){

	this->receiver = ctx->getReceiver();

	//disconnect slots first?
	QObject::connect(receiver, SIGNAL(ConnectEvent()),
	        this, SLOT(onConnect()));
	QObject::connect(receiver, SIGNAL(DisconnectEvent()),
	        this, SLOT(onDisconnect()));
	QObject::connect(receiver, SIGNAL(freqChange(const double&)),
	        this, SLOT(onFreqChange(const double&)));
	QObject::connect(receiver, SIGNAL(levelChange(int)),
	        this, SLOT(onLevelChange(int)));
	QObject::connect(receiver, SIGNAL(modeChange(int)),
	        this, SLOT(onModeChange(int)));
	QObject::connect(receiver, SIGNAL(AttChangeEvent(int)),
	        this, SLOT(onAttChange(int)));
	QObject::connect(receiver, SIGNAL(ErrorEvent(std::string&)),
	        this, SLOT(onError(std::string&)));
	QObject::connect(receiver, SIGNAL(levelSquelchChange(int)),
	        this, SLOT(onLevelSquelchChange(int)));
	QObject::connect(receiver, SIGNAL(audioSquelchChange(int)),
	        this, SLOT(onAudioSquelchChange(int)));

	//update gui

}

void MainWindow::showTuneForm ()
{
	//save location
	if (tuneForm->isVisible()) {
		tuneForm->hide();
	} else {
		tuneForm->show();
		tuneForm->raise();
		tuneForm->activateWindow();
	}
}

void MainWindow::changeLevelSquelch(int level)
{
	receiver->setLevelSquelch( level );
}

void MainWindow::onLevelSquelchChange(int level)
{
	levelSquelch->setValue(level);
	QString str;
	if(level == 0){
		str = "OFF";
	}else{
		str.setNum(level);
	}
	lblSqL->setText(str);
}

void MainWindow::changeAudioSquelch(int level)
{
	receiver->setAudioSquelch( level );
}

void MainWindow::onAudioSquelchChange(int level)
{
	audioSquelch->setValue(level);
	QString str;
	if(level == 0){
		str = "OFF";
	}else{
		str.setNum(level);
	}
	lblSqA->setText(str);
}

void MainWindow::scrollLevelSquelchLeft()
{
	int i = levelSquelch->value();
	if(i <=0 ) return;
	levelSquelch->setValue(i-1);
}

void MainWindow::scrollLevelSquelchRight()
{
	int i = levelSquelch->value();
	if(i >=255 ) return;
	levelSquelch->setValue(i+1);
}

void MainWindow::scrollAudioSquelchLeft()
{
	int i = audioSquelch->value();
	if(i <=0 ) return;
	audioSquelch->setValue(i-1);
}

void MainWindow::scrollAudioSquelchRight()
{
	int i = audioSquelch->value();
	if(i >=255 ) return;
	audioSquelch->setValue(i+1);
}






