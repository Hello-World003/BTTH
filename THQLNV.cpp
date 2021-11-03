/*Bài thực hành quản lý nhân viên*/
//Sử dụng cấu trúc danh sách liên kết kép

#include<bits/stdc++.h>
using namespace std;

struct NV       //Khai bao cau truc nhan vien
{
    char MaNV[20];
    char HoTen[70];
    char NgaySinh[12];
    long long Luong;

};

struct Node  //Tao node 
{
    NV data;
    Node *Next;
    Node *Prev;
};

struct List  //Khai bao cau truc danh sach
{
  Node *Head;
  Node *Tail;
};


void Init(List &Q)  //Khoi tao danh sach
{
    Q.Head=Q.Tail=NULL;
}


void inputNV(NV &x)  //Them thong tin mot sinh vien
{
    cout<<"Nhap ma nhan vien:";
    cin.getline(x.MaNV,20);
    cout<<"\nNhap ho va ten:";
    cin.getline(x.HoTen,70);
    cout<<"\nNhap ngay sinh:";
    cin.getline(x.NgaySinh,12);
    cout<<"\nNhap luong:";
    cin>>x.Luong;
    cin.ignore();
}


void outputNV(NV x)   //Hien thi thong tin mot nhan vien
{
    cout<<setw(12)<<x.MaNV;
    cout<<setw(30)<<x.HoTen;
    cout<<setw(12)<<x.NgaySinh;
    cout<<setw(10)<<x.Luong;
    cout<<endl;
}

Node *CreateNode(NV x)  //Tao node luu du lieu nhan vien
{
    Node *p=new Node;
    if(p==NULL)
    {
        cout<<"Khong du bo nho";
        return 0;
    }
    else{
        p->data=x;
        p->Next=NULL;
        p->Prev=NULL;
        return p;
    }
}


void insetFirst(List &Q,NV x)   //Them vao dau danh sach
{
    Node *p=CreateNode(x);
    if(Q.Head==NULL)
    {
        Q.Head=Q.Tail=p;
    }
    else{
        p->Next=Q.Head;
        Q.Head->Prev=p;
        Q.Head=p;
    }
}


void printDSNV(List Q)  //Hien thi danh sach nhan vien
{
    cout<<"Danh sach nhan vien:"<<endl;
    Node *p=Q.Head;
    cout<<setw(12)<<"MaNV"<<setw(30)<<"HovaTen"<<setw(12)<<"Ngaysinh"<<setw(10)<<"Luong"<<endl;
    while(p!=NULL)
    {
        outputNV(p->data);
        p=p->Next;
    }
}

void deleteNode(List &Q,Node *p)  //Xoa mot node khoi danh sach
{
    if(Q.Head==p)
    {
       if(Q.Head==Q.Tail)
       {
           Q.Head=Q.Tail=NULL;
       }
       else{
            Q.Head=Q.Head->Next;
           p->Next=NULL;
           Q.Head->Prev=NULL;
           delete(p);
           p=NULL;
       }
    }
    else if(Q.Tail==p){
        Q.Tail=Q.Tail->Prev;
        p->Prev=NULL;
        Q.Tail->Next=NULL;
        delete(p);
        p=NULL;
    }
    else{
        p->Prev->Next=p->Next;
        p->Next->Prev=p->Prev;
        p->Next=NULL;
        p->Prev=NULL;
        delete(p);
        p=NULL;
    }
}


void deleteNV(List &Q)  //Xoa mot nhan vien theo ma nhan vien
{
    char x[20];
    cout<<"Nhap ma nhan vien can xoa:";
    cin.getline(x,20);
    cout<<x;
    cout<<endl;
    Node *p=Q.Head;
    while(p!=NULL)
    {
        if(stricmp((p->data.MaNV),x)==0)
        {
            deleteNode(Q,p);
            break;
        }
        p=p->Next;
    }
    if(p==NULL)
    {
        cout<<"Khong co nhan vien co ma "<<x<<" trong danh sach"<<endl;
    }
    else{

         cout<<"Da xoa nhan vien co ma "<<x<<endl;
    }

}


void MaxLuongNV(List Q)   //Danh sach nhan vien co muc luong cao nhat
{
    Node *p=Q.Head;
    long long Max=p->data.Luong;
    while(p!=NULL)
    {

        if(p->data.Luong>=Max)
        {
            Max=p->data.Luong;
        }
        p=p->Next;
    }
    cout<<"Danh sach nha vien co luong cao nhat la:"<<endl<<endl;
    cout<<setw(12)<<"MaNV"<<setw(30)<<"HovaTen"<<setw(12)<<"Ngaysinh"<<setw(10)<<"Luong"<<endl;
    p=Q.Head;
    while(p!=NULL)
    {
        if(p->data.Luong==Max)
        {
            outputNV(p->data);
        }
        p=p->Next;
    }
}

/*-----------------*/

void inputDSNV(List &Q,int &n)  //Nhap vao thong tin danh sach nhan vien
{
    cout<<"Nhap so luong nhan vien:";
    cin>>n;
    cout<<endl;
    cin.ignore();
    for(int i=0;i<n;i++)
    {   NV a;
        cout<<"Nhap thong tin nhan vien thu "<<i+1<<endl;
        while(true)
        {
            inputNV(a);
            Node *p=Q.Head;
            bool kt=false;
            while(p!=NULL)
            {
                if(stricmp((p->data.MaNV),a.MaNV)==0)
                {
                    cout<<"\n>>>>>>>>>.Ma Nhan vien Da Ton Tai Vui Long Nhap Lai<<<<<<<<<<\n"<<endl;
                    kt=true;
                    break;
                }
                p=p->Next;
            }
            if(kt==false)
            {
                break;
            }

        }
        insetFirst(Q,a);
        cout<<"\n-----------------------------\n";
    }
}


void SortforLuong(List &Q)      //Sap xep giam dan theo muc luong
{
    for(Node *p=Q.Head;p!=NULL;p=p->Next)
    {
        for(Node *q=p->Next;q!=NULL;q=q->Next)
        {
            if(p->data.Luong<q->data.Luong)
            {
                NV a=p->data;
                p->data=q->data;
                q->data=a;
            }
        }
    }
    cout<<"Danh sach nhan vien sau khi sap xep theo luong la:"<<endl;
    printDSNV(Q);
}

void SortforMa(List &Q)           //Sap xep giam dan theo ma nhan vien
{
    for(Node *p=Q.Head;p!=NULL;p=p->Next)
    {
        for(Node *q=p->Next;q!=NULL;q=q->Next)
        {
            if(stricmp(p->data.MaNV,q->data.MaNV)<0)
            {
                NV a=p->data;
                p->data=q->data;
                q->data=a;
            }
        }
    }
    cout<<"Danh sach nhan vien sau khi sap xep theo ma nhanvien la:"<<endl;
    printDSNV(Q);
}


char *TachTen(char x[30])          //Tach ten ra khoi hovaten
{
    char *a=new char ;
    int countt=0;
    for(int i=strlen(x)-1;i>=0;i--)
    {
        if(x[i]==' ')
        {
            break;
        }
        a[countt]=x[i];
        countt++;
    }
     return strrev(a);
}


void SortforTen(List &Q)      //Sap xep theo ten nhan vien
{
    for(Node *p=Q.Head;p!=NULL;p=p->Next)
    {
        for(Node *q=p->Next;q!=NULL;q=q->Next)
        {
            char *a=TachTen(p->data.HoTen);
            char *b=TachTen(q->data.HoTen);
            if(stricmp(a,b)<0)
            {
                NV a=p->data;
                p->data=q->data;
                q->data=a;
            }
            delete(a);
            a=NULL;
            delete(b);
            b=NULL;
        }
    }
    cout<<"Danh sach nhan vien sau khi sap xep theo ten la:"<<endl;
    printDSNV(Q);
}

char *TachNam(char x[6])              //Tach nam sinh ra khoi ngaysinh
{
    char *a=new char ;
    int countt=0;
    for(int i=strlen(x)-1;i>=0;i--)
    {
        if(x[i]=='/')
        {
            break;
        }
        a[countt]=x[i];
        countt++;
    }
     return strrev(a);
}

void SortforNam(List &Q)        //Sap xep theo nam sinh nhan vien
{
    for(Node *p=Q.Head;p!=NULL;p=p->Next)
    {
        for(Node *q=p->Next;q!=NULL;q=q->Next)
        {
            char *a=TachNam(p->data.NgaySinh);
            char *b=TachNam(q->data.NgaySinh);
            if(stricmp(a,b)<0)
            {
                NV a=p->data;
                p->data=q->data;
                q->data=a;
            }
            delete(a);
            a=NULL;
            delete(b);
            b=NULL;
        }
    }
    cout<<"Danh sach nhan vien sau khi sap xep theo nam sinh la:"<<endl;
    printDSNV(Q);
}

void Menu()                 //Menu hien thi chinh
{
    cout<<"\n-------------------MENU------------------\n"<<endl;
    cout<<"0.Thoat"<<endl;
    cout<<"1.Them nhan vien"<<endl;
    cout<<"2.Hien thong tin danh sach nhan vien"<<endl;
    cout<<"3.Thong tin nhan vien co muc luong cao nhat"<<endl;
    cout<<"4.Xoa thong tin nhan vien"<<endl;
    cout<<"5.Sap xep nhan vien giam dan"<<endl;
    cout<<"-->Vui long chon cac lua chon tren:";
}

void MenuSort()     //Menu trong sap xep
{
    cout<<endl;
    cout<<"1.Theo luong nhan vien"<<endl;
    cout<<"2.Theo ma nhan vien"<<endl;
    cout<<"3.Theo ten nhan vien"<<endl;
    cout<<"4.Theo nam sinh nhan vien"<<endl;
    cout<<"->Vui long chon cac lua chon:";
}

int main()          //MAIN
{   List Q;
    int n;
    Init(Q);
    while(true)
    {   int tl;
        Menu();
        cin>>tl;
        cout<<endl;
        if(tl==0)
        {
            exit(0);
        }
        else if(tl==1)
        {
            inputDSNV(Q,n);
        }
        else if(tl==2)
        {
            if(Q.Head==NULL)
            {
                cout<<"..Danh sach nhan vien trong.."<<endl;
            }
            else{
                printDSNV(Q);
            }
        }
        else if(tl==3)
        {
            if(Q.Head==NULL)
            {
                cout<<"..Danh sach nhan vien trong.."<<endl;
            }
            else{
                MaxLuongNV(Q);
            }
        }
        else if(tl==4)
        {
            if(Q.Head==NULL)
            {
                cout<<"..Danh sach nhan vien trong.."<<endl;
            }
            else{
                    cin.ignore();
                deleteNV(Q);
            }
        }
        else if(tl==5)
        {   if(Q.Head==NULL)
            {
                cout<<"Danh sach nhan vien trong"<<endl;
            }


           else{
            while(true)
            {
                 int reply;
                MenuSort();
                cin>>reply;
                cout<<endl;
                 if(reply==1)
                {
                    SortforLuong(Q);
                    break;
                 }
                else if(reply==2)
               {
                  SortforMa(Q);
                  break;
               }
              else if(reply==3)
              {
                SortforTen(Q);
                break;
              }
              else if(reply==4)
              {
                SortforNam(Q);
                break;
              }
              else{
                cout<<"....Vui long chon lai...."<<endl;
              }
            }
           }
        }
        else{
            cout<<"....Vui long chon lai......"<<endl;
        }

    }

    return 0;
}
