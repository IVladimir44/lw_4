#include <Winsock2.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <msclr/marshal_cppstd.h>
#include <ctime>
#pragma comment(lib, "ws2_32.lib")

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Text;

struct Command {
    std::string comanda;
    std::vector<std::string> parameters;
};



bool breakrules = false;
int selected = 0;

std::string commanda = "";
int parameter[8];
int leng = 0;
std::string parameter2[1];
int leng2 = 0;
int painte = 0;
int j = 0;

int rand_num = 0;
bool isrand = false;


namespace KSKS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Drawing::Drawing2D;

    /// <summary>
    /// Сводка для MyForm
    /// </summary>


    public ref class MyForm : public System::Windows::Forms::Form
    {
    private:
        UdpClient^ udpServer;
    private: System::Windows::Forms::Label^ label1;

    private: System::Windows::Forms::Panel^ panel1;
           int port = 12345;
    private: System::Windows::Forms::Label^ label3;
    private: Bitmap^ Bit_map;
    public:
        MyForm(void)
        {
            InitializeComponent();
            //
            //TODO: добавьте код конструктора
            //
            udpServer = gcnew UdpClient(port);
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
            Bit_map = gcnew Bitmap(panel1->Width, panel1->Height);
        }
    private:
        void ReceiveCallback(IAsyncResult^ ar)
        {
            IPEndPoint^ endPoint = gcnew IPEndPoint(IPAddress::Any, port);
            array<Byte>^ receiveBytes = udpServer->EndReceive(ar, endPoint);
            String^ receivedMessage = Encoding::ASCII->GetString(receiveBytes);
            if (receivedMessage == "random")
            {
                isrand = true;
                std::cout << "1";
            }

            // Обработка полученного сообщения
            // Ваш код для обработки сообщения
            this->Invoke(gcnew Action<String^>(this, &MyForm::parsi), receivedMessage);
            // Продолжаем прослушивать порт
            udpServer->BeginReceive(gcnew AsyncCallback(this, &MyForm::ReceiveCallback), nullptr);
        }

    protected:
        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        ///
        void InitializeComponent(void)
        {
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->SuspendLayout();
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label1->Location = System::Drawing::Point(298, 545);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(158, 27);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Пустая строка\r\n";
            // 
            // panel1
            // 
            this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            this->panel1->Location = System::Drawing::Point(12, 12);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(749, 450);
            this->panel1->TabIndex = 2;
            this->panel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::panel1_Paint);
            // 
            // label3
            // 
            this->label3->AutoSize = true;
            this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(204)));
            this->label3->Location = System::Drawing::Point(142, 465);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(477, 55);
            this->label3->TabIndex = 3;
            this->label3->Text = L"Введенная команда";
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(773, 592);
            this->Controls->Add(this->label3);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->label1);
            this->Name = L"MyForm";
            this->Text = L"MyForm";
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void DrawRoundedRectangle(Graphics^ g, Pen^ pen, int x, int y, int width, int height, int radius)
        {
            GraphicsPath^ path = gcnew GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();


            g->DrawPath(pen, path);

            delete path;
        }

        void FillRoundedRectangle(Graphics^ g, int x, int y, int width, int height, int radius, Color fillColor)
        {
            System::Drawing::Drawing2D::GraphicsPath^ path = gcnew System::Drawing::Drawing2D::GraphicsPath();

            System::Drawing::Rectangle rect = System::Drawing::Rectangle(x, y, width, height);

            int diameter = 2 * radius;
            System::Drawing::Rectangle arc = System::Drawing::Rectangle(rect.Location, System::Drawing::Size(diameter, diameter));

            path->AddArc(arc, 180, 90);
            arc.X = rect.Right - diameter;
            path->AddArc(arc, 270, 90);
            arc.Y = rect.Bottom - diameter;
            path->AddArc(arc, 0, 90);
            arc.X = rect.Left;
            path->AddArc(arc, 90, 90);

            path->CloseFigure();

            SolidBrush^ fillBrush = gcnew SolidBrush(fillColor);
            g->FillPath(fillBrush, path);

            delete path;
            delete fillBrush;
        }

        void Draw_Text(Graphics^ g, String^ text, Color textColor, int x, int y, int fonte, int len)
        {
            System::Drawing::Font^ font;
            switch (fonte)
            {
            case 1:
                font = gcnew System::Drawing::Font("Arial", len);
                break;
            case 2:
                font = gcnew System::Drawing::Font("Times New Roman", len);
                break;
            case 3:
                font = gcnew System::Drawing::Font("Courier New", len);
                break;
            case 4:
                font = gcnew System::Drawing::Font("Verdana", len);
                break;
            case 5:
                font = gcnew System::Drawing::Font("Tahoma", len);
                break;
            case 6:
                font = gcnew System::Drawing::Font("Comic Sans MS", len);
                break;
            default:
                breakrules = true;
                break;
            }
            System::Drawing::Brush^ brush = gcnew SolidBrush(textColor);
            g->DrawString(text, font, brush, x, y);
        }

        Color MyCol()
        {
            srand(time(0));
            if (isrand == true)
            {
                parameter[j] = ((rand() % 17) + 1);
            }
            if (1 == parameter[j])
            {
                return Color::Red;
            }
            else if (2 == parameter[j])
            {
                return Color::Blue;
            }
            else if (3 == parameter[j])
            {
                return Color::Black;
            }
            else if (4 == parameter[j])
            {
                return Color::Brown;
            }
            else if (5 == parameter[j])
            {
                return Color::Green;
            }
            else if (6 == parameter[j])
            {
                return Color::White;
            }
            else if (7 == parameter[j])
            {
                return Color::Cyan;
            }
            else if (8 == parameter[j])
            {
                return Color::Yellow;
            }
            else  if (9 == parameter[j])
            {
                return Color::Magenta;
            }
            else  if (10 == parameter[j])
            {
                return Color::Gray;
            }
            else if (11 == parameter[j])
            {
                return Color::LightGray;
            }
            else  if (12 == parameter[j])
            {
                return Color::DarkGray;
            }
            else if (13 == parameter[j])
            {
                return Color::Orange;
            }
            else if (14 == parameter[j])
            {
                return Color::Pink;
            }
            else if (15 == parameter[j])
            {
                return Color::Purple;
            }
            else {
                return Color::White;
                breakrules = true;
            }
        }

        void drawImage(Graphics^ g, int x0, int y0, int w, int h, array<Color>^ imageData)
        {
            for (int x = 0; x < w; x++)
            {
                for (int y = 0; y < h; y++)
                {
                    Color pixelColor = imageData[x + y * w];
                    SolidBrush^ brush = gcnew SolidBrush(pixelColor);
                    g->FillRectangle(brush, x0 + x, y0 + y, 1, 1);
                }
            }
        }


        void StartTimer()
        {
            System::Timers::Timer^ timer = gcnew System::Timers::Timer(1000);

            timer->Elapsed += gcnew System::Timers::ElapsedEventHandler(this, &MyForm::OnTimerElapsed);

            timer->Start();
        }

        void OnTimerElapsed(System::Object^ sender, System::Timers::ElapsedEventArgs^ e)
        {
            DateTime currentTime = DateTime::Now;

            this->Invoke(gcnew Action<String^>(this, &MyForm::UpdateLabel), currentTime.ToString("HH:mm:ss"));
        }

        void UpdateLabel(String^ text)
        {
            // Обновляем текст label1
            label1->Text = text;
        }

        void parsi(String^ my_mes)
        {
            std::cout << "4";
            leng = 0;
            leng2 = 0;
            std::string my_mes1 = msclr::interop::marshal_as<std::string>(my_mes);
            check_command(my_mes1);
            std::cout << "5";
            label1->Text = my_mes;

            if (breakrules == false)
            {
                if (isrand == true)
                {
                    String^ message2 = "";
                    message2 = msclr::interop::marshal_as<String^>(commanda);
                    for (int i = 0; i < leng; i++)
                    {
                        message2 += System::Convert::ToString(parameter[i]) + " ";
                    }
                    for (int i = 0; i < leng2; i++)
                    {
                        message2 += msclr::interop::marshal_as<String^>(parameter2[i]);
                    }
                }
                std::cout << "6";

                Color colorss = MyCol();

                Graphics^ g = Graphics::FromImage(Bit_map);
                Pen^ pen = gcnew Pen(colorss, 2);
                SolidBrush^ brush = gcnew SolidBrush(colorss);


                if (painte == 1)
                {
                    Bit_map = gcnew Bitmap(panel1->Width, panel1->Height);
                    panel1->BackColor = colorss;
                    panel1->Invalidate();
                }

                if (painte == 2) {

                    g->DrawLine(pen, parameter[0], parameter[1], parameter[0] + 1, parameter[1] + 1);

                }
                if (painte == 3) {

                    g->DrawLine(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (painte == 4) {

                    g->DrawRectangle(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (painte == 5) {

                    g->FillRectangle(brush, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (painte == 6) {

                    g->DrawEllipse(pen, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (painte == 7) {

                    g->FillEllipse(brush, parameter[0], parameter[1], parameter[2], parameter[3]);
                }
                if (painte == 8)
                {

                    g->DrawEllipse(pen, parameter[0], parameter[1], parameter[2], parameter[2]);
                }
                if (painte == 9)
                {

                    g->FillEllipse(brush, parameter[0], parameter[1], parameter[2], parameter[2]);
                }
                if (painte == 10)
                {
                    DrawRoundedRectangle(g, pen, parameter[0], parameter[1], parameter[2], parameter[3], parameter[4]);
                }
                if (painte == 11)
                {
                    FillRoundedRectangle(g, parameter[0], parameter[1], parameter[2], parameter[3], parameter[4], colorss);
                }
                if (painte == 12)
                {
                    String^ textToDraw = msclr::interop::marshal_as<String^>(parameter2[0]);
                    Draw_Text(g, textToDraw, colorss, parameter[0], parameter[1], parameter[3], parameter[4]);
                }
                if (painte == 13)
                {
                    array<Color>^ imageData = gcnew array<Color>(parameter[2] * parameter[3]);

                    for (int i = 0; i < imageData->Length; i++)
                    {
                        imageData[i] = colorss;
                    }


                    drawImage(g, parameter[0], parameter[1], parameter[2], parameter[3], imageData);
                }
                delete g;
                delete pen;
                delete brush;

                panel1->Invalidate();
                painte = 0;
            }
            else {
                label1->Text = "Ошибка! Неверная команда!";
            }
            isrand = false;
            std::cout << "7";
        }


        Command check_command(const std::string& commandStr) {
            srand(time(0));
            if (isrand == true)
            {
                rand_num = ((rand() % 13) + 1);
            }
            Command command;
            std::cout << "2";

            int number;
            selected = 0;
            int i = 0;

            std::istringstream get_mes_word(commandStr);
            std::string get_word;
            get_mes_word >> command.comanda;


            while (get_mes_word >> get_word) {
                if (get_word == ":")
                {
                    break;
                }
                command.comanda += " " + get_word;
            }
            std::cout << "3";
            if (command.comanda == "clear display" || rand_num == 1) {
                j = 0;
                painte = 1;
                selected = 1;
            }
            if (command.comanda == "draw pixel" || rand_num == 2) {
                j = 2;
                painte = 2;
                selected = 10;
            }
            if (command.comanda == "draw line" || rand_num == 3) {
                j = 4;
                painte = 3;
                selected = 20;
            }
            if (command.comanda == "draw rectangle" || rand_num == 4)
            {
                j = 4;
                painte = 4;
                selected = 30;
            }
            if (command.comanda == "fill rectangle" || rand_num == 5) {
                j = 4;
                painte = 5;
                selected = 40;
            }
            if (command.comanda == "draw ellipse" || rand_num == 6) {
                j = 4;
                painte = 6;
                selected = 50;
            }
            if (command.comanda == "fill ellipse" || rand_num == 7)
            {
                j = 4;
                painte = 7;
                selected = 60;
            }
            if (command.comanda == "draw circle" || rand_num == 8)
            {
                j = 3;
                painte = 8;
                selected = 70;
            }
            if (command.comanda == "fill circle" || rand_num == 9)
            {
                j = 3;
                painte = 9;
                selected = 80;
            }
            if (command.comanda == "draw rounded rectangle" || rand_num == 10)
            {
                j = 5;
                painte = 10;
                selected = 90;
            }
            if (command.comanda == "fill rounded rectangle" || rand_num == 11)
            {
                j = 5;
                painte = 11;
                selected = 100;
            }
            if (command.comanda == "draw text" || rand_num == 12)
            {
                j = 2;
                painte = 12;
                selected = 110;
            }
            if (command.comanda == "draw image" || rand_num == 13)
            {
                j = 4;
                painte = 13;
                selected = 120;
            }
            if (command.comanda == "start timer" || rand_num == 15)
            {
                j = 1;
                painte = 15;
                selected = 150;
                StartTimer();
            }
            if (selected == 0) {
                breakrules = true;
                return command;
            }
            std::cout << "8";
            if (isrand == true)
            {
                for (int i = 0; i < 8; i++)
                {
                    parameter[i] = rand() % 200;
                }
            }
            std::cout << "9";

            if (isrand == false)
            {
                if (!breakrules)
                {
                    while (get_mes_word >> get_word) {
                        if (selected == 1 || selected >= 10 && selected <= 12 || selected >= 20 && selected <= 24 || selected >= 30 && selected <= 34
                            || selected >= 40 && selected <= 44 || selected >= 50 && selected <= 54 || selected >= 60 && selected <= 64 || selected >= 70 && selected <= 73
                            || selected >= 80 && selected <= 83 || selected >= 90 && selected <= 95 || selected >= 100 && selected <= 105 || selected >= 110 && selected <= 115
                            || selected >= 120 && selected <= 124)
                        {
                            command.parameters.push_back(get_word);
                            if (selected == 115)
                            {
                                parameter2[0] = get_word;
                                breakrules = false;
                                return command;
                            }
                            try {
                                number = stoi(get_word);
                                parameter[i] = number;
                                i++;
                            }
                            catch (const std::invalid_argument& e) {
                                breakrules = true;
                                return command;
                            }
                            breakrules = false;
                            selected++;
                        }
                    }
                    breakrules = false;
                    return command;
                }
                else {
                    return command;
                }
            }
            return command;
        }


        void mes_get(String^ message) {

        }
#pragma endregion
    private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
        e->Graphics->DrawImage(Bit_map, 0, 0);
    }
    };
}
