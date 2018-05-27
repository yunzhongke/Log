/*================================================================
*   Copyright (C) 2018 Sangfor Ltd. All rights reserved.
*   
*   文件名称：terminal.cpp
*   创 建 者：yunzhongke
*   创建日期：2018年05月27日
*   描    述：
*
================================================================*/


#include <QtGui/QIntValidator> //整形验证器
#include "terminal.h"

Termianl::Termianl(QWidget *parent) : QMainWindow(parent)
{
    m_init();

    set_tabwidget();

    set_style();

    set_connect();

    set_property();

    set_layout();


    this->setWindowTitle("终端");
}

void Termianl::m_init()
{
    tab = new QTabWidget(this);
    ter_tab = new QWidget(tab);
    port_tab = new QWidget(tab);
    output_label = new QLabel(ter_tab);
    input_label = new QLabel(ter_tab);
    text_show = new QTextEdit(ter_tab);
    line_input = new QLineEdit(ter_tab);
    store_button = new QPushButton(ter_tab);
    exit_button = new QPushButton(ter_tab);

    h_layout1 = new QHBoxLayout();
    h_layout2 = new QHBoxLayout();
    v_layout = new QVBoxLayout();
}

void Termianl::set_property()
{
    
    output_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    output_label->setText("输出区");
    output_label->setAlignment(Qt::AlignCenter);
    
    input_label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    input_label->setText("输入区");
    input_label->setAlignment(Qt::AlignCenter);

    text_show->setReadOnly(true);
    line_input->setPlaceholderText("输入选项数字");

    QIntValidator *p = new QIntValidator(this); // 验证器
    p->setRange(1 , 10);
    line_input->setValidator(p); //设置只能输入验证器指定的内容
    //line_input->setInputMask("0000-00-00 00:00:00"); //  设置按照掩码格式输入

    store_button->setText("保存");

    exit_button->setText("退出");


}

void Termianl::set_layout()
{
   h_layout1->addWidget(output_label); 
   h_layout1->addWidget(text_show); 
   h_layout1->addWidget(store_button);

   h_layout2->addWidget(input_label);
   h_layout2->addWidget(line_input);
   h_layout2->addWidget(exit_button);

   v_layout->addLayout(h_layout1);
   v_layout->addLayout(h_layout2);

   ter_tab->setLayout(v_layout);
}

void Termianl::set_connect()
{
    QObject::connect(line_input , SIGNAL(returnPressed()) , this , SLOT(clear_text()));
}

void Termianl::set_style()
{

}

void Termianl::clear_text()
{
    text_show->insertPlainText(line_input->text() + '\n');
    text_show->moveCursor(QTextCursor::End); //将光标移到到写入的地方 
    //text_show->setText(line_input->text());
    line_input->clear();
}

void Termianl::set_tabwidget()
{
    this->setCentralWidget(tab);

    tab->addTab(port_tab , "串口");
    tab->addTab(ter_tab , "终端");


}

Termianl::~Termianl()
{

}
