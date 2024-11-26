#pragma once
#include <msclr/marshal_cppstd.h>

#include "..\stack\TCalc.h"
#include "..\stack\TStack.h"


namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private:


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;



	private: System::Void button1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		button1->BackColor = System::Drawing::Color::SteelBlue;
	}

	private: System::Void button1_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		button1->BackColor = System::Drawing::Color::SkyBlue;
	}



#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::DeepSkyBlue;
			this->button1->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->ForeColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->button1->Location = System::Drawing::Point(248, 125);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(163, 71);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Получить результат";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Bookman Old Style", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(47, 251);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(123, 23);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Результат: ";
			// 
			// textBox1
			// 
			this->textBox1->BackColor = System::Drawing::Color::BlanchedAlmond;
			this->textBox1->Location = System::Drawing::Point(51, 71);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(563, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::textBox1_KeyDown);
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Bookman Old Style", 12));
			this->label2->Location = System::Drawing::Point(212, 35);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(231, 23);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Введите выражение: ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Bookman Old Style", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(47, 299);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(233, 23);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Постфиксная форма: ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Thistle;
			this->ClientSize = System::Drawing::Size(670, 428);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"Калькулятор";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		System::String^ input = textBox1->Text;		// получаем текст из textBox1

		// Конвертируем System::String^ в std::string
		std::string infixExpression = msclr::interop::marshal_as<std::string>(input);

		TCalc calc;			// создаем объект калькулятора
		calc.SetInfix(infixExpression);		// устанавливаем инфиксное выражение

		
		calc.ToPostfix();			// преобразуем в постфиксное выражение
		if (calc.GetPostfix().empty())
		{
			label1->Text = "Ошибка: не удалось преобразовать выражение!";
			label3->Text = "Нельзя вывести постфиксную форму!";

			return;
		}

		double result = calc.CalcPostfix();		// вычисляем результат
		if (std::isnan(result) || std::isinf(result))
		{
			label1->Text = "Ошибка: некорректный результат!";
			label3->Text = "Нельзя вывести постфиксную форму!";
			return;
		}

		std::string ress = calc.GetPostfix();
		label1->Text = "Результат выражения: " + result.ToString();		// выводим результат
		label3->Text = "Постфиксная форма: " + gcnew System::String(ress.c_str());
	}
	

private: System::Void textBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) 
{
	if (e->KeyCode == Keys::Enter)
	{
		button1->PerformClick();
	}
}

};
}
