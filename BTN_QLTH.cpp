#include <iostream>
#include <fstream> //thư viện để đọc ghi file
#include <vector>
#include <string>
#include <cmath> //thư viện để làm tròn
#include <iomanip> //thư viện để lấp đầy khoảng trắng
#include <algorithm> //thư viện để sắp xếp
#include <sstream> //thư viện để sử dụng stringstream
#include <map>

using namespace std;

string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first != string::npos && last != string::npos)
               ? str.substr(first, last - first + 1)
               : "";
}
//Nhập file
ifstream fileinGV("GiaoVien.txt");
ifstream fileinHS("HocSinh.txt");
ifstream fileinBD("BangDiem.txt");

//lớp Giáo viên
class GiaoVien {
    public:
        string maGV, tenGV, monDay, sdt;
        bool tt = true;
        void nhapGV() {
            cout << "Nhap ma giao vien: "; cin >> maGV;
            cout << "Nhap ten giao vien: "; cin.ignore(); getline(cin, tenGV);
            cout << "Nhap mon day: "; getline(cin, monDay);
            cout << "Nhap so dien thoai: "; cin >> sdt;
            tt = true;
        }
        void xuatGV() const {
            cout << left << setfill(' ') << setw(10) << maGV << setw(20) << tenGV << setw(15) << monDay << setw(15) << sdt << endl;
        }
    };

//lớp Học sinh
class HocSinh {
    public:
        string maHS, tenHS, lop, diaChi, sdt, sdtPH;
        bool tt = true;
        void nhapHS() {
            cout << "Nhap ma hoc sinh: "; cin >> maHS;
            cout << "Nhap ten hoc sinh: "; cin.ignore(); getline(cin, tenHS);
            cout << "Nhap lop: "; cin >> lop;
            cout << "Nhap dia chi: "; cin.ignore(); getline(cin, diaChi);
            cout << "Nhap so dien thoai: "; cin >> sdt;
            cout << "Nhap so dien thoai phu huynh: "; cin >> sdtPH;
            tt = true;
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

// Đọc dữ liệu từ file Giáo viên
vector<GiaoVien> docGiaoVienTuFile(const string& tenFile) 
    {
        vector<GiaoVien> dsgv;
        ifstream filein(tenFile); 
        if (!filein) {
            cout << "Khong the mo file " << tenFile << "!" << endl;
            return dsgv;
        }
        string line;
        while (getline(filein, line)) { // đọc từng dòng trong file và lưu vào biến line
            stringstream ss(line); // tạo ra một string stream từ dòng vừa đọc, Chuyển dòng đọc được thành luồng chuỗi
            GiaoVien gv;
            getline(ss, gv.maGV, ',');
            getline(ss, gv.tenGV, ',');
            getline(ss, gv.monDay, ',');
            getline(ss, gv.sdt, ',');
            dsgv.push_back(gv);
        }
        filein.close();
        return dsgv;
    }

// Đọc dữ liệu từ file Học sinh
vector<HocSinh> docHocSinhTuFile(const string& tenFile) 
    {
        vector<HocSinh> dshs;
        ifstream filein(tenFile); 
        if (!filein) {
            cout << "Khong the mo file " << tenFile << "!" << endl;
            return dshs;
        }
        string line;
        while (getline(filein, line)) { // đọc từng dòng trong file và lưu vào biến line
            stringstream ss(line); // tạo ra một string stream từ dòng vừa đọc, Chuyển dòng đọc được thành luồng chuỗi
            HocSinh hs;
            getline(ss, hs.maHS, ',');
            getline(ss, hs.tenHS, ',');
            getline(ss, hs.lop, ',');
            // getline(ss, hs.diaChi, ',');
            if (ss.peek() == '"') { // Kiểm tra nếu địa chỉ bắt đầu bằng dấu "
                ss.get(); // Bỏ qua dấu "
                getline(ss, hs.diaChi, '"'); // Đọc đến dấu " tiếp theo
                ss.get(); // Bỏ qua dấu , sau dấu "
            } else {
                getline(ss, hs.diaChi, ',');
            }
            getline(ss, hs.sdt, ',');
            getline(ss, hs.sdtPH, ',');
            dshs.push_back(hs);
        }
        filein.close();
        return dshs;
    }

// Đọc dữ liệu từ file Bảng điểm
vector<BangDiem> docBangDiemTuFile(const string& tenFile) 
    {
        vector<BangDiem> dsbd;
        ifstream filein(tenFile); 
        if (!filein) {
            cout << "Khong the mo file " << tenFile << "!" << endl;
            return dsbd;
        }
        string line;
        while (getline(filein, line)) { // đọc từng dòng trong file và lưu vào biến line
            stringstream ss(line); // tạo ra một string stream từ dòng vừa đọc, Chuyển dòng đọc được thành luồng chuỗi
            BangDiem bd;
            getline(ss, bd.maHS, ',');
            getline(ss, bd.maMH, ',');
            ss >> bd.DM; ss.ignore();
            ss >> bd.DCC; ss.ignore();
            ss >> bd.DKT; ss.ignore();
            ss >> bd.DT;
            dsbd.push_back(bd);
        }
        filein.close();
        return dsbd;
    }

//ghi file Giáo Viên
void ghiFileGV(const string& tenFile, const vector<GiaoVien>& dsgv) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& gv : dsgv) { // duyệt qua từng phần tử trong vector
        fileout << gv.maGV << "," << gv.tenGV << "," << gv.monDay << "," << gv.sdt << endl;
    }
    fileout.close();
}

//ghi file Học Sinh
void ghiFileHS(const string& tenFile, const vector<HocSinh>& dshs) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& hs : dshs) { // duyệt qua từng phần tử trong vector
        fileout << hs.maHS << "," << hs.tenHS << "," << hs.lop << ","
                << hs.diaChi << "," << hs.sdt << "," << hs.sdtPH << endl;
    }
    fileout.close();
}

//ghi file Bảng Điểm
void ghiFileBD(const string& tenFile, const vector<BangDiem>& dsbd) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& bd : dsbd) { // duyệt qua từng phần tử trong vector
        fileout << bd.maHS << "," << bd.maMH << "," << bd.DM << "," << bd.DCC << "," << bd.DKT << "," << bd.DT << endl;
    }
    fileout.close();
}

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

// void pauseAndClear() {
//     cout << "\nNhan Enter de tiep tuc...";
//     //system("pause");
//     cin.ignore();
//     cin.get();
//  //   system("cls"); // Xóa màn hình
// }
void pauseAndClear() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
    cin.get(); // Đợi Enter từ người dùng
    // system("cls"); // Nếu cần xóa màn hình trên Windows
}

int main()
{
    vector<HocSinh> dshs;
    vector<GiaoVien> dsgv;
    vector<BangDiem> dsbd;
    int chon;
    int ok;
    do
    {
        // system("cls");
        menu();
        cin >> chon;
        switch (chon)
        {
            case 1: //Nhập học sinh
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
                
                char luu;
                cout << "Ban co muon luu vao file? (Y/N): ";
                cin >> luu;
                if (luu == 'Y' || luu == 'y') {
                    ghiFileHS("HocSinh.txt", dshs);
                    cout << "Da them thanh cong!" << endl;
                }
                pauseAndClear();
                break;   
            };

            case 2: //Nhập giáo viên
            {
                int soLuong;
                cout << "Nhap so luong giao vien: ";
                cin >> soLuong;
                for (int i = 0; i < soLuong; i++) {
                    GiaoVien gv;
                    cout << "Nhap thong tin giao vien thu " << i + 1 << ":"<< endl;
                    gv.nhapGV();
                    dsgv.push_back(gv);
                }
                
                char save;
                cout << "Ban co muon luu vao file? (Y/N): ";
                cin >> save;
                if (save == 'Y' || save == 'y') {
                    ghiFileGV("GiaoVien.txt", dsgv);
                    cout << "Da them thanh cong!" << endl;
                }
                pauseAndClear();
                break;
            };
            
            case 3: //nhập bảng điểm
            {
                if (dshs.empty()) {
                    cout << "Danh sach hoc sinh dang trong! \n";
                    break;
                }
                
                if (dshs.empty()) {
                    cout << "Danh sach hoc sinh dang trong! \n";
                    break;
                }
                
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


                char save;
                cout << "Ban co muon luu vao file? (Y/N): ";
                cin >> save;
                if (save == 'Y' || save == 'y') {
                    ghiFileBD("BangDiem.txt", dsbd);
                    cout << "Da them thanh cong!" << endl;
                }
                pauseAndClear();
                break;
            };

            case 4: {
                vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
                if (dsgv.empty()) {
                    cout << "Khong co du lieu giao vien!\n";
                    break;
                }
                
                // Sắp xếp theo tên (ưu tiên Firstname)
                sort(dsgv.begin(), dsgv.end(), [](const GiaoVien &a, const GiaoVien &b) {
                    return a.tenGV < b.tenGV;
                });
                
                cout << "\n=============== DANH SACH GIAO VIEN ===============\n";
                cout << "| " << left << setw(15) << "Ma giao vien" << setw(25) << "Ten giao vien" << setw(8) << "Mon day" << "|"<< endl;
                cout << "---------------------------------------------------\n";
                for (const auto& gv : dsgv) {
                    cout << "|     " << left << setw(10) << gv.maGV << setw(25) << gv.tenGV << setw(8) << gv.monDay << " |" << endl;
                }
                cout << "===================================================\n";
                
                char save;
                cout << "Ban co muon luu danh sach vao file? (Y/N): ";
                cin >> save;
                if (tolower(save) == 'y') {
                    ofstream fileout("DanhSachGiaoVien.txt");
                    fileout << "\n=============== DANH SACH GIAO VIEN ===============\n";
                    fileout <<  "| " << left << setw(15) << "Ma giao vien" << setw(25) << "Ten giao vien" << setw(8) << "Mon day" << "|"<< endl;
                    fileout << "---------------------------------------------------\n";
                    for (const auto& gv : dsgv) {
                        fileout << "|     " << left << setw(10) << gv.maGV << setw(25) << gv.tenGV << setw(8) << gv.monDay << " |" << endl;
                    }
                    fileout << "===================================================\n";
                    fileout.close();
                    cout << "Danh sach da duoc luu vao file DanhSachGiaoVien.txt\n";
                }
                pauseAndClear();
                break;
            };
            
            case 5: {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                if (dshs.empty()) {
                    cout << "Khong co du lieu hoc sinh!\n";
                    break;
                }
            
                // Hàm tách họ, tên đệm, tên chính
                auto splitName = [](const string &fullName) {
                    istringstream iss(fullName);
                    vector<string> words;
                    string word;
                    while (iss >> word) {
                        words.push_back(word);
                    }
                    string ho = words.empty() ? "" : words.front();  // Họ
                    string ten = words.size() > 1 ? words.back() : "";  // Tên chính
                    string tenDem = words.size() > 2 ? words[1] : "";  // Tên đệm (nếu có)
                    return make_tuple(ho, tenDem, ten);
                };
            
                sort(dshs.begin(), dshs.end(), [&](const HocSinh &a, const HocSinh &b) {
                    auto [hoA, demA, tenA] = splitName(a.tenHS);
                    auto [hoB, demB, tenB] = splitName(b.tenHS);
                    
                    if (tenA != tenB) return tenA < tenB;  // Ưu tiên theo tên chính
                    if (demA != demB) return demA < demB;  // Nếu tên chính giống nhau, xét tên đệm
                    return hoA < hoB;  // Nếu tên chính + tên đệm giống nhau, xét họ
                });
            
                // Hiển thị danh sách đã sắp xếp
                cout << "\n=================================================== DANH SACH HOC SINH =========================================================\n" << endl;
                cout << "| " << left << setw(15) << "Ma hoc sinh"
                    << setw(20) << "Ten hoc sinh"
                    << setw(10) << "Lop"
                    << setw(50) << "Dia chi"
                    << setw(15) << "SDT"
                    << setw(15) << "SDT phu huynh" << "|" << endl;
                cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
            
                for (const auto &hs : dshs) {
                    cout << "| " << left << setw(15) << hs.maHS
                        << setw(20) << hs.tenHS
                        << setw(10) << hs.lop
                        << setw(50) << hs.diaChi
                        << setw(15) << hs.sdt
                        << setw(15) << hs.sdtPH << "|" << endl;
                }
                cout << "================================================================================================================================\n";
                
                char save;
                cout << "Ban co muon luu danh sach vao file? (Y/N): ";
                cin >> save;
                if (tolower(save) == 'y') {
                    ofstream fileout("DanhSachHocSinh.txt");
                    fileout << "\n=================================================== DANH SACH HOC SINH =========================================================\n"<<endl;
                    fileout <<"| " << left << setw(15) << "Ma hoc sinh"
                            << setw(20) << "Ten hoc sinh"
                            << setw(10) << "Lop"
                            << setw(50) << "Dia chi"
                            << setw(15) << "SDT"
                            << setw(15) << "SDT phu huynh" << "|"<< endl;
                    fileout << "--------------------------------------------------------------------------------------------------------------------------------\n";
                    for (const auto& hs : dshs) {
                        // Nếu địa chỉ chứa dấu "," thì bọc lại trong dấu ngoặc kép
                        string diaChiLuuFile = hs.diaChi;
                        if (diaChiLuuFile.find(',') != string::npos) {
                            diaChiLuuFile = '"' + diaChiLuuFile + '"';
                        }
            
                        fileout <<"| " << left << setw(15) << hs.maHS
                                << setw(20) << hs.tenHS
                                << setw(10) << hs.lop
                                << setw(50) << diaChiLuuFile  // Ghi địa chỉ có hoặc không có ""
                                << setw(15) << hs.sdt
                                << setw(15) << hs.sdtPH << "|"<< endl;
                    }
                    fileout << "================================================================================================================================\n";
                    fileout.close();
                    cout << "Danh sach da duoc luu vao file DanhSachHocSinh.txt\n";
                }
                pauseAndClear();
                break;
            };        
            
            case 6: {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
                
                if (dshs.empty() || dsbd.empty()) {
                    cout << "Khong co du lieu!\n";
                    break;
                }
                
                string maHS;
                cout << "Nhap ma hoc sinh: ";
                cin >> maHS;
                
                HocSinh hs;
                bool found = false;
                for (const auto& h : dshs) {
                    if (h.maHS == maHS) {
                        hs = h;
                        found = true;
                        break;
                    }
                }
                
                if (!found) {
                    cout << "Khong tim thay hoc sinh voi ma " << maHS << "!\n";
                    break;
                }
                
                cout<<endl;
                cout <<setfill(' ')<<setw(50)<< "BANG DIEM CUA HOC SINH " << hs.tenHS << setfill(' ')<<endl;
                cout << "Ma Hoc Sinh: " << hs.maHS << endl;
                cout << "Ten Hoc Sinh: " <<hs.tenHS<< endl;
                cout << "Lop: "<< hs.lop << endl;                
                cout << "\n===================================================================================\n";
                cout <<"| " << left << setw(10) << "Mon Hoc" << setw(15) << "Diem mieng" << setw(15) << "Diem TX" << setw(15) << "Diem KT" << setw(15) << "Diem Thi" << setw(10) << "Diem TB" <<"| ";
                cout << "\n-----------------------------------------------------------------------------------\n";
                for (const auto& bd : dsbd) {
                    if (bd.maHS == maHS) {
                        cout << "| " <<left << setw(10) << bd.maMH << setw(15) << bd.DM << setw(15) << bd.DCC << setw(15) << bd.DKT << setw(15) << bd.DT << setw(10) << bd.diemTB() <<"| " << endl;
                    }
                }           
                cout << "===================================================================================\n";
                char save;
                cout << "Ban co muon luu bang diem vao file? (Y/N): ";
                cin >> save;
                if (tolower(save) == 'y') {
                    ofstream fileout("BangDiem_" + maHS + ".txt");
                    fileout<<endl;                
                    fileout << setfill(' ')<<setw(50)<< "BANG DIEM CUA HOC SINH " << hs.tenHS << setfill(' ')<<endl;
                    fileout <<  "Ma Hoc Sinh: " << hs.maHS << endl;
                    fileout << "Ten Hoc Sinh: " <<hs.tenHS<< endl;
                    fileout <<  "Lop: "<< hs.lop << endl;                    
                    fileout << "\n===================================================================================\n";
                    fileout << "| " <<left << setw(10) << "Mon Hoc" << setw(15) << "Diem mieng" << setw(15) << "Diem TX" << setw(15) << "Diem KT" << setw(15) << "Diem Thi" << setw(10) << "Diem TB" << "|"<< endl;
                    fileout << "-----------------------------------------------------------------------------------\n";
                    for (const auto& bd : dsbd) {
                        if (bd.maHS == maHS) {
                            fileout <<"| " << left << setw(10) << bd.maMH << setw(15) << bd.DM << setw(15) << bd.DCC << setw(15) << bd.DKT << setw(15) << bd.DT << setw(10) << bd.diemTB() << "|"<< endl;
                        }
                    }              
                    fileout << "===================================================================================\n";
                    fileout.close();
                    cout << "Bang diem da duoc luu vao file BangDiem_" << maHS << ".txt\n";
                }
                pauseAndClear();
                break;
            }
            
            case 7: {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
      
                if (dshs.empty() || dsbd.empty()) {
                    cout << "Khong co du lieu!\n";
                    break;
                }
      
                string maMH;
                cout << "Nhap ma mon hoc: ";
                cin >> maMH;
      
                // Lọc điểm theo môn học
                vector<BangDiem> diemTheoMon;
                for (const auto& bd : dsbd) {
                    if (trim(bd.maMH) == trim(maMH)) {
                        diemTheoMon.push_back(bd);
                    }
                }
      
                if (diemTheoMon.empty()) {
                    cout << "Khong co du lieu diem cho mon hoc " << maMH << "!\n";
                    break;
                }
      
                // Hiển thị danh sách điểm theo môn học
                cout << "\n=================== DANH SACH DIEM THEO MON " << maMH << " ====================\n"<<endl;
                cout <<"=====================================================================\n";
                cout << "|"<<left << setw(15) << "Ma hoc sinh" << setw(10) << "Ma mon" << setw(8) << "Mieng" << setw(8) << "15 phut" << setw(8) << "KT" << setw(8) << "Thi" << setw(10) << "Diem TB" <<"|"<< endl;
                cout<<"---------------------------------------------------------------------\n";
                for (const auto& bd : diemTheoMon) {
                    // Tìm tên học sinh tương ứng
                    string tenHS;
                    for (const auto& hs : dshs) {
                        if (hs.maHS == bd.maHS) {
                            tenHS = hs.tenHS;
                            break;
                        }
                    }
                    cout << "|"<< left << setw(15) << bd.maHS 
                         << setw(10) << bd.maMH 
                         << setw(8) << bd.DM 
                         << setw(8) << bd.DCC 
                         << setw(8) << bd.DKT 
                         << setw(8) << bd.DT 
                         << setw(10) << bd.diemTB() <<"|"<< endl; // now displays all details
                }      
                cout<<"=====================================================================\n";
      
                // Có muốn lưu danh sách ra file không?
                char save;
                cout << "Ban co muon luu danh sach vao file? (Y/N): ";
                cin >> save;
      
                if (save == 'Y' || save == 'y') {
                    ofstream fileout("DanhSachDiemTheoMon_" + trim(maMH) + ".txt");
                    fileout << "\n=================== DANH SACH DIEM THEO MON " << maMH << " ====================\n"<<endl;
                    fileout<<"=======================================================================\n";
                    fileout << "|"<<left << setw(15) << "Ma hoc sinh" << setw(10) << "Ma mon" << setw(8) << "Mieng" << setw(8) << "15 phut" << setw(8) << "KT" << setw(8) << "Thi" << setw(10) << "Diem TB" << "|"<<endl;
                    fileout<<"---------------------------------------------------------------------\n";
                    for (const auto& bd : diemTheoMon) {
                        // Tìm tên học sinh tương ứng
                        string tenHS;
                        for (const auto& hs : dshs) {
                            if (hs.maHS == bd.maHS) {
                                tenHS = hs.tenHS;
                                break;
                            }
                        }
                        fileout <<"|"<< left << setw(15) << bd.maHS 
                                << setw(10) << bd.maMH 
                                << setw(8) << bd.DM 
                                << setw(8) << bd.DCC 
                                << setw(8) << bd.DKT 
                                << setw(8) << bd.DT 
                                << setw(10) << bd.diemTB() <<"|"<< endl; // now displays all details
                    }
                    fileout<<"=====================================================================\n";
                    fileout.close();
                    cout << "Danh sach da duoc luu vao file DanhSachDiemTheoMon_" << trim(maMH) << ".txt\n";
                }
      
                pauseAndClear();
                break;
            }

            case 8: //báo cáo kết quả học tập theo lớp
            {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

                if (dshs.empty() || dsbd.empty()) {
                    cout << "Khong co du lieu!\n";
                    break;
                }

                string lop;
                cout << "Nhap lop: ";
                cin >> lop;

                //Lọc học sinh theo lớp
                vector<HocSinh> hsTheoLop;
                for(const auto& hs : dshs)
                {
                    if(hs.lop == lop)
                    {
                        hsTheoLop.push_back(hs);
                    }
                }

                if(hsTheoLop.empty())
                {
                    cout << "Khong co hoc sinh nao trong lop " << lop << "!\n";
                    break;
                }

                //Tạo danh sách môn học
                map<string, bool> monHocMap;
                vector<string> DSMonHoc;
                for(const auto& bd : dsbd)
                {
                    if(!monHocMap[bd.maMH]) //Nếu môn học chưa có trong danh sách
                    {
                        DSMonHoc.push_back(bd.maMH);
                        monHocMap[bd.maMH] = true; //Nếu thêm r đánh dấu true
                    }
                }

                //Hiển thị báo cáo
                cout << "\n================================= BAO CAO KET QUA HOC TAP - LOP " << lop << " ====================================\n"<<endl;
                cout <<"| " << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh";
                for (const auto& mon : DSMonHoc) {
                    cout << setw(10) << mon;
                }
                cout  <<"Diem TB" << "|"<< endl;
                cout << "---------------------------------------------------------------------------------------------------------\n";
                // In dữ liệu điểm của từng học sinh
                for (const auto& hs : hsTheoLop) {
                    cout << "|    "<< left << setw(13) << hs.maHS << setw(20) << hs.tenHS;
                    float TB = 0;
                    int dem = 0;

                    for (const auto& mon : DSMonHoc) {
                        float diemTB = 0; // nếu không có điểm
                        for (const auto& bd : dsbd) {
                            if (bd.maHS == hs.maHS && bd.maMH == mon) {
                                diemTB = bd.diemTB();
                                break;
                            }
                        }

                        if (diemTB == 0) {
                            cout << setw(10) << "N/A"; // Không có điểm
                        } else {
                            cout << setw(10) << diemTB ;
                        }
                        TB += diemTB;
                        dem++;
                    }
                    cout << left << setw(6)<<round((TB/dem)*100)/100 <<"|"<< endl;
                }
                cout << "=========================================================================================================\n";

                // có muốn in ra file không
                char in;
                cout << "Ban co muon luu bao cao vao file? (Y/N): ";
                cin >> in;
                ofstream fileout;

                if (in == 'Y' || in == 'y') {
                    ofstream fileout("BaoCaoHocTap.txt");
                    // In báo cáo vào file
                    fileout << "\n=============================== BAO CAO KET QUA HOC TAP - LOP " << lop << " ======================================\n"<<endl;
                    fileout << "| " <<left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh";
                    for (const auto& mon : DSMonHoc) {
                        fileout  << setw(10) << mon;
                    }
                    fileout <<"Diem TB" <<"|"<< endl;
                    fileout << "---------------------------------------------------------------------------------------------------------\n";
                    // In dữ liệu điểm của từng học sinh vào file
                    for (const auto& hs : hsTheoLop) {
                        fileout <<"|    " << left << setw(13) << hs.maHS << setw(20) << hs.tenHS;
                        float TB = 0;
                        int dem = 0;
            
                        for (const auto& mon : DSMonHoc) {
                            float diemTB = 0; // nếu không có điểm
                            for (const auto& bd : dsbd) {
                                if (bd.maHS == hs.maHS && bd.maMH == mon) {
                                    diemTB = bd.diemTB();
                                    break;
                                }
                            }
            
                            if (diemTB == 0) {
                                fileout << setw(10) << "N/A"; // Không có điểm
                            } else {
                                fileout << setw(10) << diemTB;
                            }
                            TB += diemTB;
                            dem++;
                        }
                        fileout << left << setw(6)<<round((TB / dem) * 100) / 100 <<"|"<< endl;
                        
                    }
                    fileout << "=========================================================================================================\n";
                    fileout.close();
                    cout << "Bao cao da duoc luu vao file BaoCaoHocTap.txt\n";
                }

                pauseAndClear();
                break;
            };

            case 9: //In danh sách điểm trung bình của học sinh
            {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

                if (dshs.empty() || dsbd.empty()) {
                    cout << "Khong co du lieu!\n";
                    break;
                }

                string lop;
                cout << "Nhap lop: ";
                cin >> lop;

                //Lọc học sinh theo lớp
                vector<HocSinh> hsTheoLop;
                for(const auto& hs : dshs)
                {
                    if(hs.lop == lop)
                    {
                        hsTheoLop.push_back(hs);
                    }
                }

                if(hsTheoLop.empty())
                {
                    cout << "Khong co hoc sinh nao trong lop " << lop << "!\n";
                    break;
                }

                //Hiển thị báo cáo
                cout << "\n==== BAO CAO DIEM TRUNG BINH HOC SINH - LOP " << lop << " ====\n";
                cout << "| "<< left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(15) << "Diem TB" << "| " <<endl;
                cout << "-----------------------------------------------------\n";
                // In dữ liệu điểm của từng học sinh 
                for (const auto& hs : hsTheoLop) {
                    float tongDiem = 0;
                    int soMon = 0;

                    for (const auto& bd : dsbd) {
                        if (bd.maHS == hs.maHS) {
                            tongDiem += bd.diemTB(); 
                            soMon++; 
                        }
                    }

                    // Nếu học sinh có điểm ở ít nhất một môn
                    float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1; // Tính điểm trung bình

                    cout <<"| "<< left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
                    if (diemTB == -1) {
                        cout << setw(15) << "N/A" <<"|"<< endl;
                    } else {
                        cout << setw(15) << round(diemTB * 100) / 100 <<"|"<< endl;
                    }
                }           
                cout << "=====================================================\n";
   
                //Có in file ko?
                char in;
                cout << "Ban co muon luu bao cao vao file? (Y/N): ";
                cin >> in;

                if(in == 'Y' || in == 'y')
                {
                    ofstream fileDTB("DiemTrungBinhHocSinh.txt");
                    // In báo cáo vào file
                    fileDTB << "\n==== BAO CAO DIEM TRUNG BINH HOC SINH - LOP " << lop << " ====\n";
                    fileDTB <<"| "<< left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(15) << "Diem TB" << "|"<< endl;
                    fileDTB << "-----------------------------------------------------\n";
                    // In dữ liệu điểm của từng học sinh vào file
                    for (const auto& hs : hsTheoLop) {
                        float tongDiem = 0;
                        int soMon = 0;

                        for (const auto& bd : dsbd) {
                            if (bd.maHS == hs.maHS) {
                                tongDiem += bd.diemTB(); 
                                soMon++; 
                            }
                        }

                        // Tính điểm tb
                        float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1; // Tính điểm trung bình

                        fileDTB <<"| "<< left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
                        if (diemTB == -1) {
                            fileDTB << setw(15) << "N/A" <<"|"<< endl;
                        } else {
                            fileDTB << setw(15) << round(diemTB * 100) / 100 <<"|"<< endl;
                        }
                    }
                    fileDTB << "=====================================================\n";
                    fileDTB.close();
                    cout << "Bao cao da duoc luu vao file DiemTrungBinhHocSinh.txt\n";
                }
                pauseAndClear();
                break;
            };

            case 10: { // Hiển thị học sinh có điểm trung bình cao nhất
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
            
                if (dshs.empty() || dsbd.empty()) {
                    cout << "Khong co du lieu de hien thi!\n";
                    break;
                }
            
                float maxDiemTB = 0;
                vector<HocSinh> hsMaxDiemTB;
            
                // Tính điểm trung bình cho tất cả các môn của từng học sinh
                for (const auto& hs : dshs) {
                    float tongDiem = 0;
                    int soMon = 0;
            
                    for (const auto& bd : dsbd) {
                        if (bd.maHS == hs.maHS) {
                            tongDiem += bd.diemTB();
                            soMon++;
                        }
                    }
            
                    float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1;
                    diemTB = round(diemTB * 100) / 100;
            
                    // Tìm học sinh có điểm trung bình cao nhất
                    if (diemTB > maxDiemTB) {
                        maxDiemTB = diemTB;
                        hsMaxDiemTB.clear();
                        hsMaxDiemTB.push_back(hs);
                    } else if (diemTB == maxDiemTB) {
                        hsMaxDiemTB.push_back(hs);
                    }
                }
            
                // Hiển thị danh sách học sinh có điểm trung bình cao nhất
                cout << "\nHoc sinh co diem trung binh cao nhat:\n";
                cout <<"| "<< left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(8) << "TB" <<"|"<< endl;
            
                for (const auto& hs : hsMaxDiemTB) {
                    cout <<"| "<< left << setw(10) << hs.maHS << setw(20) << hs.tenHS << setw(10) << hs.lop;
                    cout << setw(8) << maxDiemTB <<"|"<< endl;
                }
            
                pauseAndClear();
                break;
            }            

            case 11: {
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
      
                if (dshs.empty() && dsgv.empty()) {
                    cout << "Khong co du lieu de tim kiem!\n";
                    break;
                }
      
                string keyword;
                cout << "Nhap ten hoac ma de tim kiem: ";
                cin.ignore();
                getline(cin, keyword);
      
                // Tìm kiếm học sinh
                bool foundStudent = false;
                for (const auto& hs : dshs) {
                    if (hs.tenHS.find(keyword) != string::npos || hs.maHS.find(keyword) != string::npos) {
                        if (!foundStudent) {
                            cout << "\nKet qua tim kiem hoc sinh:\n";
                            cout << left << setw(15) << "Ma hoc sinh"
                                << setw(20) << "Ten hoc sinh"
                                << setw(10) << "Lop"
                                << setw(50) << "Dia chi"
                                << setw(15) << "SDT"
                                << setw(15) << "SDT phu huynh"<< endl;
                            foundStudent = true;  // Set to true on first match
                        }
                        // hs.xuatHS();
                        
                            cout  << left << setw(15) << hs.maHS
                                << setw(20) << hs.tenHS
                                << setw(10) << hs.lop
                                << setw(50) << hs.diaChi
                                << setw(15) << hs.sdt
                                << setw(15) << hs.sdtPH << endl;
                        
                    }
                }
                if (!foundStudent) {
                    cout << "Khong tim thay hoc sinh nao.\n";
                }
      
                // Tìm kiếm giáo viên
                bool foundTeacher = false;
                for (const auto& gv : dsgv) {
                    if (gv.tenGV.find(keyword) != string::npos || gv.maGV.find(keyword) != string::npos) {
                        if (!foundTeacher) {
                            cout << "\nKet qua tim kiem giao vien:\n";
                            cout << left << setw(15) << "Ma giao vien" << setw(20) << "Ten giao vien" << setw(10) << "Mon day" << setw(15) << "SDT" << endl;
                            foundTeacher = true;  // Set to true on first match
                        }
                        // gv.xuatGV();
                        cout << left << setw(13) << gv.maGV
                            << setw(20) << gv.tenGV
                            << setw(10) << gv.monDay
                            << setw(15) << gv.sdt << endl;
                    }
                }
                if (!foundTeacher) {
                    cout << "Khong tim thay giao vien nao.\n";
                }
                pauseAndClear();
                break;
            };

            case 12: //xếp loại học lực
            {   
                vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

    if (dshs.empty() || dsbd.empty()) {
        cout << "Khong co du lieu de hien thi!\n";
        break;
    }

    string lop;
    cout << "Nhap lop: ";
    cin >> lop;

    // Lọc học sinh theo lớp
    vector<HocSinh> hsTheoLop;
    for (const auto& hs : dshs) {
        if (hs.lop == lop) {
            hsTheoLop.push_back(hs);
        }
    }

    if (hsTheoLop.empty()) {
        cout << "Khong co hoc sinh nao trong lop " << lop << "!\n";
        break;
    }

    // Hiển thị tiêu đề báo cáo
    cout << "\n============ XEP LOAI HOC LUC - LOP " << lop << " ============\n";
    cout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(10) << "Diem TB" << setw(15) << "Hoc luc" << endl;

    // Xếp loại học lực
    for (const auto& hs : hsTheoLop) {
        float tongDiem = 0;
        int soMon = 0;

        // Tính điểm trung bình của học sinh
        for (const auto& bd : dsbd) {
            if (bd.maHS == hs.maHS) {
                tongDiem += bd.diemTB(); 
                soMon++; 
            }
        }

        float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1;

        // Xác định học lực
        string hocLuc;
        if (diemTB >= 9) {
            hocLuc = "Xuat sac";
        } else if (diemTB >= 8) {
            hocLuc = "Gioi";
        } else if (diemTB >= 6.5) {
            hocLuc = "Kha";
        } else if (diemTB >= 5) {
            hocLuc = "Trung binh";
        } else {
            hocLuc = "Yeu";
        }

        // Hiển thị kết quả
        cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS << setw(10) << round(diemTB * 100) / 100 << setw(15) << hocLuc << endl;
    }
    cout << "========================================================\n";

    // Có muốn lưu kết quả ra file không?
    char save;
    cout << "Ban co muon luu ket qua vao file? (Y/N): ";
    cin >> save;

    if (save == 'Y' || save == 'y') {
        ofstream fileout("XepLoaiHocLuc.txt");
        fileout << "\n============ XEP LOAI HOC LUC - LOP " << lop << " ============\n";
        fileout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(10) << "Diem TB" << setw(15) << "Hoc luc" << endl;

        // Lưu kết quả vào file
        for (const auto& hs : hsTheoLop) {
            float tongDiem = 0;
            int soMon = 0;

            for (const auto& bd : dsbd) {
                if (bd.maHS == hs.maHS) {
                    tongDiem += bd.diemTB(); 
                    soMon++; 
                }
            }

            float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1;

            string hocLuc;
            if (diemTB >= 9) {
                hocLuc = "Xuat sac";
            } else if (diemTB >= 8) {
                hocLuc = "Gioi";
            } else if (diemTB >= 6.5) {
                hocLuc = "Kha";
            } else if (diemTB >= 5) {
                hocLuc = "Trung binh";
            } else {
                hocLuc = "Yeu";
            }

            fileout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS << setw(10) << round(diemTB * 100) / 100 << setw(15) << hocLuc << endl;
        }
        fileout << "========================================================\n";
        fileout.close();
        cout << "Ket qua da duoc luu vao file XepLoaiHocLuc.txt\n";
    }

    pauseAndClear();
    break;
                
            };

            case 0: {
                cout << "Ban co thuc su muon thoat chuong trinh khong? (Y/N): ";
                char a;
                cin >> a;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ nhớ đệm
            
                if (a == 'Y' || a == 'y') {
                    return 0;
                } else {
                    pauseAndClear();
                }
                break;
            }
            
            
            default:{
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                pauseAndClear();
                // cout << "Chon chuc nang: ";
                cin.ignore();
                cin.get();
            }
        } 
    }       
    while (chon!=0);

    return 0;
}
