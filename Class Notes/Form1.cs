using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e)
        {
            lblOperator->Text = "+";
            lblOp1->Text = tbOp1->Text;
            lblOp2->Text = tbOp2->Text;
        }
        private: System::Void btnSub_Click(System::Object^ sender, System::EventArgs^ e)
        {
            lblOperator->Text = "-";
            lblOp1->Text = tbOp1->Text;
            lblOp2->Text = tbOp2->Text;
        }
        private: System::Void btnMult_Click(System::Object^ sender, System::EventArgs^ e)
        {
            lblOperator->Text = "*";
            lblOp1->Text = tbOp1->Text;
            lblOp2->Text = tbOp2->Text;
        }
        private: System::Void btnDiv_Click(System::Object^ sender, System::EventArgs^ e)
        {
            lblOperator->Text = "/";
            lblOp1->Text = tbOp1->Text;
            lblOp2->Text = tbOp2->Text;
        }

        private System::Void btnEquals_Click(System::Object^ sender, System::EventArgs^ else){
            char op;
            double x, y ,r;
            op= System::Convert::ToChar(lblOperator->Text);
            x = System::Convert::ToDouble(tbOp1->Text);
            y = System::Convert::ToDouble(tbOp2->Text);

        switch (op)
        {
        case "+": 
            r = x + y;
            break;
        case "-": 
            r = x - y;
            break;
        case "*": 
            r = x * y;
            break;
        case "/": 
            r = x / y;
            break;
        }
        lblResult->Text = System::Convert::ToString(r);
    }
    

