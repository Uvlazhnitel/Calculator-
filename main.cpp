#include <wx/wx.h>
#include <sstream>  // Для работы со строковыми потоками

// Класс основного окна (Frame)
class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title);

private:
    wxTextCtrl* textCtrl;
    wxButton* button1;
    wxButton* button2;
    wxButton* button3;
    wxButton* button4;
    wxButton* button5;
    wxButton* button6;
    wxButton* button7;
    wxButton* button8;
    wxButton* button9;
    wxButton* button0;
    wxButton* buttonPlus;
    wxButton* buttonMinus;
    wxButton* buttonEquals;
    wxButton* buttonBack;


    void OnButtonClick(wxCommandEvent& event);  // Обработчик для чисел и операторов
    void OnEqualsClick(wxCommandEvent& event);  // Обработчик для кнопки "="
    void OnButtonBack(wxCommandEvent& event);
};

// Класс приложения (App)
class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

// Реализация метода OnInit
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame("Calculator");
    frame->Show(true);
    return true;
}

// Реализация конструктора класса MyFrame
MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300))
{
    wxPanel* panel = new wxPanel(this, wxID_ANY);
    panel->SetBackgroundColour(wxColour(255, 150, 168));

    // Создание текстового поля
    textCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 10), wxSize(280, 30), wxTE_READONLY);
    textCtrl->SetBackgroundColour(*wxLIGHT_GREY);
    wxGridSizer* gridSizer = new wxGridSizer(4, 4, 0, 1);

    // Создание кнопок
    button0 = new wxButton(panel, wxID_ANY, "0");
    button1 = new wxButton(panel, wxID_ANY, "1");
    button2 = new wxButton(panel, wxID_ANY, "2");
    button3 = new wxButton(panel, wxID_ANY, "3");
    button4 = new wxButton(panel, wxID_ANY, "4");
    button5 = new wxButton(panel, wxID_ANY, "5");
    button6 = new wxButton(panel, wxID_ANY, "6");
    button7 = new wxButton(panel, wxID_ANY, "7");
    button8 = new wxButton(panel, wxID_ANY, "8");
    button9 = new wxButton(panel, wxID_ANY, "9");
    buttonPlus = new wxButton(panel, wxID_ANY, "+");
    buttonEquals = new wxButton(panel, wxID_ANY, "=");
    buttonBack = new wxButton(panel, wxID_ANY, "<-");
    buttonMinus = new wxButton(panel, wxID_ANY, "-");

    gridSizer->Add(button1,1,wxEXPAND);
    gridSizer->Add(button2,1,wxEXPAND);
    gridSizer->Add(button3,1,wxEXPAND);
    gridSizer->AddStretchSpacer();
    gridSizer->Add(button4,1,wxEXPAND);
    gridSizer->Add(button5,1,wxEXPAND);
    gridSizer->Add(button6,1,wxEXPAND);
    gridSizer->Add(buttonPlus,1,wxEXPAND);
    gridSizer->Add(button7,1,wxEXPAND);
    gridSizer->Add(button8,1,wxEXPAND);
    gridSizer->Add(button9,1,wxEXPAND);
    gridSizer->Add(buttonMinus,1,wxEXPAND);
    gridSizer->AddStretchSpacer();
    gridSizer->Add(button0,1,wxEXPAND);
    gridSizer->Add(buttonBack,1,wxEXPAND);
    gridSizer->Add(buttonEquals,1,wxEXPAND);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    // Добавление текстового поля с небольшим отступом сверху
    mainSizer->Add(textCtrl, 0, wxEXPAND | wxALL, 10);

    // Добавление сетки с кнопками в основной компоновщик с отступом сверху
    mainSizer->Add(gridSizer, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 20); // Добавляем отступ сверху в 20 пикселей
    panel->SetSizer(mainSizer);


    button0->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button1->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button2->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button3->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button4->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button5->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button6->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button7->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button8->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    button9->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    buttonPlus->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    buttonEquals->Bind(wxEVT_BUTTON, &MyFrame::OnEqualsClick, this);
    buttonBack->Bind(wxEVT_BUTTON, &MyFrame::OnButtonBack, this);
    buttonMinus->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);

}

void MyFrame::OnButtonClick(wxCommandEvent& event)
{
    wxButton* button = static_cast<wxButton*>(event.GetEventObject());
    wxString label = button->GetLabel();

    textCtrl->AppendText(label);
}

void MyFrame::OnEqualsClick(wxCommandEvent& event)
{
    // Получаем строку из текстового поля
    wxString expression = textCtrl->GetValue();
    std::string expr(expression.mb_str());  // Конвертируем wxString в std::string

    int result = 0;
    int currentNumber = 0;
    char lastOperator = '+';  // Начальный оператор - сложение

    // Проходим по каждому символу в строке
    for (size_t i = 0; i < expr.length(); ++i)
    {
        char c = expr[i];

        if (isdigit(c))
        {
            // Если символ - цифра, добавляем его к текущему числу
            currentNumber = currentNumber * 10 + (c - '0');
        }
        else if (c == '+' || c == '-')
        {
            // Если символ - оператор, выполняем предыдущую операцию
            if (lastOperator == '+')
            {
                result += currentNumber;
            }
            else if (lastOperator == '-')
            {
                result -= currentNumber;
            }

            // Обновляем текущий оператор и сбрасываем текущее число
            lastOperator = c;
            currentNumber = 0;
        }
    }

    // Обработка последнего числа после окончания цикла
    if (lastOperator == '+')
    {
        result += currentNumber;
    }
    else if (lastOperator == '-')
    {
        result -= currentNumber;
    }

    // Очищаем поле и выводим результат
    textCtrl->Clear();
    textCtrl->AppendText(wxString::Format("%d", result));
}


void MyFrame::OnButtonBack(wxCommandEvent& event){
    wxString currentText = textCtrl->GetValue();

    int length = currentText.Length();

    if(length >0){
        textCtrl->Remove(length-1, length);
    }
}

