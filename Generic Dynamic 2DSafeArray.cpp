//Programmer : Syed Mustufa Qadri
//Dated : 14th September,2018

//Header Files
#include<iostream>
#include <stdio.h>
#include <string.h>
#include<cstddef>
//Macro
#define LL long long

using namespace std;

template<class T>
class DynamicSafeArray2D //Class Definition Started
{
    private:
        T **Elements;
        LL *Rows;
        LL *Cols;
    public:
        // Null Constructor
        DynamicSafeArray2D()
        {
            Rows=new LL;
            Cols=new LL;
            *Rows=*Cols=0;
            Elements=new T*[*Rows];
            for(int i=0;i<*Rows;i++)
            {
                (*(Elements + i))=new T[*Cols];
            }
        }
        //Parameterized Constructor
        DynamicSafeArray2D(LL Rows,LL Cols)
        {
            CreateObject(Rows,Cols);
        }
        //Copy Constructor
        DynamicSafeArray2D(const DynamicSafeArray2D<T>&RHS)
        {
            this->CreateObject(*(RHS.Rows),*(RHS.Cols));
            for(int i=0;i<*Rows;i++)
                {
                    for(int j=0;j<*Cols;j++)
                    {
                        (*(*(Elements + i) + j))=(*(*(RHS.Elements + i) + j));
                    }
                }
        }
        void UpdateOrder(LL Rows,LL Cols)
        {
            if( (*(this->Rows))!=Rows || (*(this->Cols))!=Cols)
            {
                DeleteObject();
                CreateObject(Rows,Cols);
                for(int i=0;i<(*(this->Rows));i++)
                {
                    cout<<"Row "<<i+1<<" : ";
                    for(int j=0;j<(*(this->Cols));j++)
                    {
                        cin>>(*(*(Elements + i) + j));
                    }
                    cout<<endl;
                }
            }
        }
        //Assignment Operator Overloaded
        DynamicSafeArray2D<T>& operator =(const DynamicSafeArray2D<T> &RHS)
        {
            if(this!=&RHS)
            {
                this->DeleteObject();
                this->CreateObject(*(RHS.Rows),*(RHS.Cols));
                for(int i=0;i<*Rows;i++)
                {
                    for(int j=0;j<*Cols;j++)
                    {
                       (*(*(Elements + i) + j))=(*(*(RHS.Elements + i) + j));
                    }
                }
            }
            return (*this);
        }
        //Addition Operator Overloaded
        DynamicSafeArray2D<T> operator +(DynamicSafeArray2D<T> &RHS)
		{
            DynamicSafeArray2D<T> D(*(RHS.Rows),*(RHS.Cols));
            for(int i=0;i<*Rows;i++)
            {
                for(int j=0;j<*Cols;j++)
                {
                    (*(*(D.Elements + i) + j))=(*(*(Elements + i) + j))+(*(*(RHS.Elements + i) + j));
                }
            }
            return D;
		}
        //Creation Mechanism
        void CreateObject(LL Rows,LL Cols)
        {
            if(Rows<0||Cols<0)
            {
                cout<<"\n\n*** Invalid Size Give ***";
                exit(0);
            }
            this->Rows=new LL;
            this->Cols=new LL;
            *(this->Rows)=Rows;
            *(this->Cols)=Cols;
            Elements=new T*[*(this->Rows)];
            for(int i=0;i<Rows;i++)
            {
                (*(Elements + i))=new T[*(this->Cols)];
            }
        }
        //Deletion Mechanism
        void DeleteObject()
        {
            if(Elements!=0)
            {
                for(int i=(*Cols)-1;i>=0;i--)
                {
                    delete[] (*(Elements+i));
                }
                delete [] Elements;
                delete Rows;
                delete Cols;
            }
            Elements=0;
            Rows=Cols=0;
        }
        //Destructor
        ~DynamicSafeArray2D()
        {
            DeleteObject();
        }
        //Insertion Operator
        template <class U>
        friend ostream& operator <<(ostream &op, DynamicSafeArray2D<U> D);
        //Extraction Operator
        template <class U>
		friend istream& operator >>(istream &op, DynamicSafeArray2D<U> &D);

};//Class Definition Ended
template<class T>
ostream& operator <<(ostream &op, DynamicSafeArray2D<T> D)
{
    for(int i=0;i<*(D.Rows);i++)
    {
        cout<<" | ";
        for(int j=0;j<*(D.Cols);j++)
        {
            cout<<(*(*(D.Elements + i) + j)) <<" ";
        }
        cout<<"|";
        cout<<endl;
    }
//	return op;
	return cout;
}
template<class T>
istream& operator >>(istream &op, DynamicSafeArray2D<T> &D)
{
    for(int i=0;i<*(D.Rows);i++)
    {
        cout<<"Row "<<i+1<<" : ";
        for(int j=0;j<*(D.Cols);j++)
        {
            op>>(*(*(D.Elements + i) + j));
        }
        cout<<endl;
    }
//	return op;
	return cin;
}

//Driver Program Started
int main()
{
    cout<<"*** GENERIC 2D DYNAMIC SAFE ARRAY ***\n\n";
    // Matrix A
    DynamicSafeArray2D<string> MatA(3,3);
    cout<<"Enter Matrix A (3x3)\n\n";
    cin>>MatA;

    // Matrix B
    DynamicSafeArray2D<string> MatB(3,3);
    cout<<"\nEnter Matrix B (3x3)\n\n";
    cin>>MatB;

    // Addition MatA + MatB
    DynamicSafeArray2D<string> MatC(3,3);
    MatC=MatA+MatB;
    cout<<"\n  Matrix A\n\n";
    cout<<MatA;
    cout<<"\n     + \n";
    cout<<"\n  Matrix B\n\n";
    cout<<MatB;
    cout<<"\n     = \n";
    cout<<"\n  Matrix C\n\n";
    cout<<MatC;

    // Copy Constructor
    DynamicSafeArray2D<string> MatD(MatC);
    cout<<"\n*** Matrix D created by copy constructor MATRIX D(MATRIX C) ***\n\n";
    cout<<MatD;

    // Assignment Operator
    MatD=MatB;
    cout<<"\n*** Matrix D is updated by assignment operator MATRIX D = MATRIX B ***\n\n";
    cout<<MatD;

    // Reorder Matrix
    cout<<"\n\nRe Order Matrix D";
    LL Rows,Cols;
    cout<<"\n\nEnter Rows : ";
    cin>>Rows;
    cout<<"\nEnter Columns : ";
    cin>>Cols;
    cout<<endl;
    MatD.UpdateOrder(Rows,Cols);
    cout<<"\n*** UPDATED MATRIX D ***\n\n";
    cout<<MatD;
    return 0;
}
//Driver Program Ended
