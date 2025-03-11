#include <iostream>
#include <fstream> //thư viện để đọc ghi file
#include <vector>
#include <string>
#include <cmath> //thư viện để làm tròn
#include <iomanip> //thư viện để lấp đầy khoảng trắng
#include <algorithm> //thư viện để sắp xếp

using namespace std;

//Nhập file
ifstream fileinGV("GiaoVien.txt");
ifstream fileinHS("HocSinh.txt");
ifstream fileinBD("BangDiem.txt");

//lớp Giáo viên
class GiaoVien {
    public:
        string maGV, tenGV, monDay, sdt;
        void nhapGV() {
            cout << "Nhap ma giao vien: "; cin >> maGV;
            cout << "Nhap ten giao vien: "; cin.ignore(); getline(cin, tenGV);
            cout << "Nhap mon day: "; getline(cin, monDay);
            cout << "Nhap so dien thoai: "; cin >> sdt;
        }
        void xuatGV() const {
            cout << left << setfill(' ') << setw(10) << maGV << setw(20) << tenGV << setw(15) << monDay << setw(15) << sdt << endl;
        }
    };

//lớp Học sinh
class HocSinh {
    public:
        string maHS, tenHS, lop, diaChi, sdt, sdtPH;
        void nhapHS() {
            cout << "Nhap ma hoc sinh: "; cin >> maHS;
            cout << "Nhap ten hoc sinh: "; cin.ignore(); getline(cin, tenHS);
            cout << "Nhap lop: "; cin >> lop;
            cout << "Nhap dia chi: "; cin.ignore(); getline(cin, diaChi);
            cout << "Nhap so dien thoai: "; cin >> sdt;
            cout << "Nhap so dien thoai phu huynh: "; cin >> sdtPH;
        }
        void xuatHS() const {
            cout << left << setfill(' ') << setw(10) << maHS << setw(20) << tenHS << setw(10) << lop << setw(20) << diaChi << setw(15) << sdt << setw(15) << sdtPH << endl;
        }
    };

//lớp Bảng điểm
class BangDiem{
    public:
        string maHS, maMH;
        float DM, DCC, DKT, DT;

        // BangDiem(string ma, string mon, float m, float cc, float kt, float t)
        // {
        //     maHS = ma;
        //     maMH = mon;
        //     DM = m;
        //     DCC = cc;
        //     DKT = kt;
        //     DT = t;
        // }
        
        void nhapDiem() {
            cout << "Nhap ma hoc sinh: "; cin >> maHS;
            cout << "Nhap ma mon hoc: "; cin >> maMH;
            cout << "Nhap diem mieng: "; cin >> DM;
            cout << "Nhap diem 15 phut: "; cin >> DCC;
            cout << "Nhap diem kiem tra: "; cin >> DKT;
            cout << "Nhap diem thi: "; cin >> DT;
        }
        float diemTB() const {
            return round((DM + DCC + DKT*2 + DT*3) / 7*100)/100; //làm tròn đến 2 số thập phân
        }
        void xuatDiem() const {
            cout << left << setfill(' ') << setw(10) << maHS << setw(10) << maMH << setw(8) << DM
                << setw(8) << DCC << setw(8) << DKT << setw(8) << DT
                << setw(8) << diemTB() << endl;
        }
    };


//menu
void menu() {
    cout << "\n========================= MENU =========================" << endl;
    cout << "|1. Nhap sinh vien                                     |"<< endl;
    cout << "|2. Nhap giao vien                                     |"<< endl;
    cout << "|3. Nhap bang diem                                     |" << endl;
    cout << "|4. In danh sach giao vien                             |" << endl;
    cout << "|5. In danh sach sinh vien                             |" << endl;
    cout << "|6. In danh sach diem theo sinh vien                   |" << endl;
    cout << "|7. In danh sach diem theo mon                         |" << endl;
    cout << "|8. Bao cao ket qua hoc tap theo lop                   |" << endl;
    cout << "|9. In danh sach diem trung binh cua sinh vien         |" << endl;
    cout << "|10. Hien thi sinh vien co diem trung binh cao nhat    |" << endl;
    cout << "|11. Tim kiem                                          |" << endl;
    cout << "|12. Xep loai hoc luc                                  |" << endl;
    cout << "|0. Thoat                                              |" << endl;
    cout << "========================================================" << endl;
    cout << "Chon chuc nang: ";
}


int main()
{
    vector<HocSinh> dshs;
    vector<GiaoVien> dsgv;
    vector<BangDiem> dsbd;
    int chon;

    do
    {
        menu();
        cin >> chon;
        switch (chon)
        {
            case 1:
            {
                int soLuong;
                cout << "Nhap so luong hoc sinh: ";
                cin >> soLuong;
                for (int i = 0; i < soLuong; i++) {
                    HocSinh hs;
                    cout << "Nhap thong tin sinh vien thu " << i + 1 << ":" << endl;
                    hs.nhapHS();
                    dshs.push_back(hs);
                }
                cout << "Da them thanh cong!" << endl;
                system("pause");
                break;   
            };
            case 2: {
                int soLuong;
                cout << "Nhap so luong giao vien: ";
                cin >> soLuong;
                for (int i = 0; i < soLuong; i++) {
                    GiaoVien gv;
                    cout << "Nhap thong tin giao vien thu " << i + 1 << ":";
                    gv.nhapGV();
                    dsgv.push_back(gv);
                }
                cout << "Da them thanh cong!" << endl;
                system("pause");
                break;
            };
            
            case 3:{ //nhập bảng điểm
                int monHoc;
                cout << "Nhap mon hoc can nhap diem: ";
                cin >> monHoc;
                for (int i = 0; i < dshs.size(); i++) {
                    BangDiem bd;
                    cout << "Nhap diem cho hoc sinh " << dshs[i].maHS << " - " << dshs[i].tenHS << ": " << endl;
                    bd.maHS = dshs[i].maHS; 
                    bd.maMH = monHoc; 
                    cout << "Nhap diem mieng: "; cin >> bd.DM;
                    cout << "Nhap diem 15 phut: "; cin >> bd.DCC;
                    cout << "Nhap diem kiem tra: "; cin >> bd.DKT;
                    cout << "Nhap diem thi: "; cin >> bd.DT;
                    dsbd.push_back(bd); 
                }
                cout << "Da them thanh cong!" << endl;
                system("pause");
                break;
            };

            case 4:{//in danh sách giáo viên
                
            };

            case 5:{
                
            };

            case 6:{
                
            };

            case 7:{
                
            };

            case 8:{
                
            };

            case 9:{
                
            };

            case 10:{
                
            };

            case 11:{
                
            };

            case 12:{
                
            };
            
            default:{
                system("cls"); // Xóa màn hình nếu lựa chọn không hợp lệ
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Chon chuc nang: ";
                cin.ignore();
                cin.get();
            }
        } 
    }       
    while (chon != 0);

    return 0;
}