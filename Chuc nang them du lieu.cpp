#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Cấu trúc cho giáo viên
struct GiaoVien {
    string MGV;
    string TenGV;
    string MonDay;
    string SDT;
};

// Cấu trúc cho học sinh
struct HocSinh {
    string MaHS;
    string TenHS;
    string Lop;
    string DiaChi;
    string SDT;
    string SDTPH;
};

// Cấu trúc cho điểm
struct Diem {
    string MaHS;
    string MaMH;
    float DM;
    float DCC;
    float DKT;
    float DT;
};

// Hàm hiển thị menu chính
void displayMainMenu() {
    cout << "Menu:\n";
    cout << "1. Quan ly sinh vien\n";
    cout << "2. Quan ly giao vien\n";
    cout << "3. Quan ly diem\n";
    cout << "4. Thoat\n";
    cout << "Chon chuc nang: ";
}

// Hàm hiển thị submenu cho sinh viên, giáo viên, điểm
void displaySubMenu(const string& entity) {
    cout << "Quan ly " << entity << ":\n";
    cout << "1. Them du lieu\n";
    cout << "2. Sua du lieu\n";
    cout << "3. Xoa du lieu\n";
    cout << "4. Quay lai\n";
    cout << "Chon chuc nang: ";
}

// Hàm xác nhận lưu hoặc xóa
bool confirmAction(const string& action) {
    string confirm;
    cout << "Ban co chac chan muon " << action << "? (y/n): ";
    getline(cin, confirm);
    return (confirm == "y" || confirm == "Y");
}

// Hàm nhập dữ liệu giáo viên
void themGiaoVien() {
    GiaoVien gv;
    cout << "Nhap MGV: ";
    getline(cin, gv.MGV);
    cout << "Nhap TenGV: ";
    getline(cin, gv.TenGV);
    cout << "Nhap MonDay: ";
    getline(cin, gv.MonDay);
    cout << "Nhap SDT: ";
    getline(cin, gv.SDT);
    cout << "Da them giao vien thanh cong.\n";

    if (confirmAction("luu du lieu")) {
        ofstream outFile("GiaoVien.txt", ios::app);
        if (outFile.is_open()) {
            outFile << gv.MGV << "|" << gv.TenGV << "|" << gv.MonDay << "|" << gv.SDT << endl;
            outFile.close();
            cout << "Du lieu da duoc luu vao file GiaoVien.txt.\n";
        }
        else {
            cout << "Khong the mo file GiaoVien.txt de ghi.\n";
        }
    }
    else {
        cout << "Du lieu khong duoc luu.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm nhập dữ liệu học sinh
void themHocSinh() {
    HocSinh hs;
    cout << "Nhap MaHS: ";
    getline(cin, hs.MaHS);
    cout << "Nhap TenHS: ";
    getline(cin, hs.TenHS);
    cout << "Nhap Lop: ";
    getline(cin, hs.Lop);
    cout << "Nhap DiaChi: ";
    getline(cin, hs.DiaChi);
    cout << "Nhap SDT: ";
    getline(cin, hs.SDT);
    cout << "Nhap SDTPH: ";
    getline(cin, hs.SDTPH);
    cout << "Da them sinh vien thanh cong.\n";

    if (confirmAction("luu du lieu")) {
        ofstream outFile("sinhvien.txt", ios::app);
        if (outFile.is_open()) {
            outFile << hs.MaHS << "|" << hs.TenHS << "|" << hs.Lop << "|" << hs.DiaChi << "|" << hs.SDT << "|" << hs.SDTPH << endl;
            outFile.close();
            cout << "Du lieu da duoc luu vao file SinhVien.txt.\n";
        }
        else {
            cout << "Khong the mo file SinhVien.txt de ghi.\n";
        }
    }
    else {
        cout << "Du lieu khong duoc luu.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm nhập dữ liệu điểm
void themDiem() {
    Diem diem;
    cout << "Nhap MaHS: ";
    getline(cin, diem.MaHS);
    cout << "Nhap MaMH: ";
    getline(cin, diem.MaMH);
    cout << "Nhap DM: ";
    cin >> diem.DM;
    cout << "Nhap DCC: ";
    cin >> diem.DCC;
    cout << "Nhap DKT: ";
    cin >> diem.DKT;
    cout << "Nhap DT: ";
    cin >> diem.DT;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Da them diem thanh cong.\n";

    if (confirmAction("luu du lieu")) {
        ofstream outFile("diem.txt", ios::app);
        if (outFile.is_open()) {
            outFile << diem.MaHS << "|" << diem.MaMH << "|" << diem.DM << "|" << diem.DCC << "|" << diem.DKT << "|" << diem.DT << endl;
            outFile.close();
            cout << "Du lieu da duoc luu vao file BangDiem.txt.\n";
        }
        else {
            cout << "Khong the mo file BangDiem.txt de ghi.\n";
        }
    }
    else {
        cout << "Du lieu khong duoc luu.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm xóa dữ liệu sinh viên
void xoaHocSinh() {
    string maHS;
    cout << "Nhap MaHS can xoa: ";
    getline(cin, maHS);

    vector<HocSinh> danhSachHS;
    ifstream inFile("sinhvien.txt");
    bool found = false;
    HocSinh hs;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, hs.MaHS, '|');
            getline(ss, hs.TenHS, '|');
            getline(ss, hs.Lop, '|');
            getline(ss, hs.DiaChi, '|');
            getline(ss, hs.SDT, '|');
            getline(ss, hs.SDTPH, '|');

            if (hs.MaHS == maHS) {
                found = true;
                cout << "Thong tin sinh vien:\n";
                cout << "MaHS: " << hs.MaHS << ", TenHS: " << hs.TenHS << ", Lop: " << hs.Lop
                    << ", DiaChi: " << hs.DiaChi << ", SDT: " << hs.SDT << ", SDTPH: " << hs.SDTPH << endl;
                if (!confirmAction("xoa sinh vien nay")) {
                    danhSachHS.push_back(hs);
                }
            }
            else {
                danhSachHS.push_back(hs);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay sinh vien voi MaHS: " << maHS << endl;
        }
        else {
            ofstream outFile("sinhvien.txt");
            for (const auto& sv : danhSachHS) {
                outFile << sv.MaHS << "|" << sv.TenHS << "|" << sv.Lop << "|" << sv.DiaChi << "|" << sv.SDT << "|" << sv.SDTPH << endl;
            }
            outFile.close();
            cout << "Da xoa sinh vien thanh cong.\n";
        }
    }
    else {
        cout << "Khong the mo file SinhVien.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm xóa dữ liệu giáo viên
void xoaGiaoVien() {
    string mgv;
    cout << "Nhap MGV can xoa: ";
    getline(cin, mgv);

    vector<GiaoVien> danhSachGV;
    ifstream inFile("GiaoVien.txt");
    bool found = false;
    GiaoVien gv;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, gv.MGV, '|');
            getline(ss, gv.TenGV, '|');
            getline(ss, gv.MonDay, '|');
            getline(ss, gv.SDT, '|');

            if (gv.MGV == mgv) {
                found = true;
                cout << "Thong tin giao vien:\n";
                cout << "MGV: " << gv.MGV << ", TenGV: " << gv.TenGV << ", MonDay: " << gv.MonDay
                    << ", SDT: " << gv.SDT << endl;
                if (!confirmAction("xoa giao vien nay")) {
                    danhSachGV.push_back(gv);
                }
            }
            else {
                danhSachGV.push_back(gv);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay giao vien voi MGV: " << mgv << endl;
        }
        else {
            ofstream outFile("giaovien.txt");
            for (const auto& g : danhSachGV) {
                outFile << g.MGV << "|" << g.TenGV << "|" << g.MonDay << "|" << g.SDT << endl;
            }
            outFile.close();
            cout << "Da xoa giao vien thanh cong.\n";
        }
    }
    else {
        cout << "Khong the mo file GiaoVien.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm xóa dữ liệu điểm
void xoaDiem() {
    string maHS, maMH;
    cout << "Nhap MaHS: ";
    getline(cin, maHS);
    cout << "Nhap MaMH: ";
    getline(cin, maMH);

    vector<Diem> danhSachDiem;
    ifstream inFile("diem.txt");
    bool found = false;
    Diem diem;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, diem.MaHS, '|');
            getline(ss, diem.MaMH, '|');
            ss >> diem.DM; ss.ignore();
            ss >> diem.DCC; ss.ignore();
            ss >> diem.DKT; ss.ignore();
            ss >> diem.DT;

            if (diem.MaHS == maHS && diem.MaMH == maMH) {
                found = true;
                cout << "Thong tin diem:\n";
                cout << "MaHS: " << diem.MaHS << ", MaMH: " << diem.MaMH << ", DM: " << diem.DM
                    << ", DCC: " << diem.DCC << ", DKT: " << diem.DKT << ", DT: " << diem.DT << endl;
                if (!confirmAction("xoa diem nay")) {
                    danhSachDiem.push_back(diem);
                }
            }
            else {
                danhSachDiem.push_back(diem);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay diem voi MaHS: " << maHS << " va MaMH: " << maMH << endl;
        }
        else {
            ofstream outFile("diem.txt");
            for (const auto& d : danhSachDiem) {
                outFile << d.MaHS << "|" << d.MaMH << "|" << d.DM << "|" << d.DCC << "|" << d.DKT << "|" << d.DT << endl;
            }
            outFile.close();
            cout << "Da xoa diem thanh cong.\n";
        }
    }
    else {
        cout << "Khong the mo file BangDiem.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm cập nhật dữ liệu sinh viên
void suaHocSinh() {
    string maHS;
    cout << "Nhap MaHS can sua: ";
    getline(cin, maHS);

    vector<HocSinh> danhSachHS;
    ifstream inFile("SinhVien.txt");
    bool found = false;
    HocSinh hs;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, hs.MaHS, '|');
            getline(ss, hs.TenHS, '|');
            getline(ss, hs.Lop, '|');
            getline(ss, hs.DiaChi, '|');
            getline(ss, hs.SDT, '|');
            getline(ss, hs.SDTPH, '|');

            if (hs.MaHS == maHS) {
                found = true;
                cout << "Thong tin sinh vien hien tai:\n";
                cout << "MaHS: " << hs.MaHS << ", TenHS: " << hs.TenHS << ", Lop: " << hs.Lop
                    << ", DiaChi: " << hs.DiaChi << ", SDT: " << hs.SDT << ", SDTPH: " << hs.SDTPH << endl;

                cout << "Nhap thong tin moi:\n";
                cout << "Nhap TenHS: ";
                getline(cin, hs.TenHS);
                cout << "Nhap Lop: ";
                getline(cin, hs.Lop);
                cout << "Nhap DiaChi: ";
                getline(cin, hs.DiaChi);
                cout << "Nhap SDT: ";
                getline(cin, hs.SDT);
                cout << "Nhap SDTPH: ";
                getline(cin, hs.SDTPH);

                if (confirmAction("sua sinh vien nay")) {
                    danhSachHS.push_back(hs);
                    cout << "Da sua sinh vien thanh cong.\n";
                }
                else {
                    cout << "Huy sua.\n";
                }
            }
            else {
                danhSachHS.push_back(hs);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay sinh vien voi MaHS: " << maHS << endl;
        }
        else {
            ofstream outFile("SinhVien.txt");
            for (const auto& sv : danhSachHS) {
                outFile << sv.MaHS << "|" << sv.TenHS << "|" << sv.Lop << "|" << sv.DiaChi << "|" << sv.SDT << "|" << sv.SDTPH << endl;
            }
            outFile.close();
        }
    }
    else {
        cout << "Khong the mo file SinhVien.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm cập nhật dữ liệu giáo viên
void suaGiaoVien() {
    string mgv;
    cout << "Nhap MGV can sua: ";
    getline(cin, mgv);

    vector<GiaoVien> danhSachGV;
    ifstream inFile("GiaoVien.txt");
    bool found = false;
    GiaoVien gv;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, gv.MGV, '|');
            getline(ss, gv.TenGV, '|');
            getline(ss, gv.MonDay, '|');
            getline(ss, gv.SDT, '|');

            if (gv.MGV == mgv) {
                found = true;
                cout << "Thong tin giao vien hien tai:\n";
                cout << "MGV: " << gv.MGV << ", TenGV: " << gv.TenGV << ", MonDay: " << gv.MonDay
                    << ", SDT: " << gv.SDT << endl;

                cout << "Nhap thong tin moi:\n";
                cout << "Nhap TenGV: ";
                getline(cin, gv.TenGV);
                cout << "Nhap MonDay: ";
                getline(cin, gv.MonDay);
                cout << "Nhap SDT: ";
                getline(cin, gv.SDT);

                if (confirmAction("sua giao vien nay")) {
                    danhSachGV.push_back(gv);
                    cout << "Da sua giao vien thanh cong.\n";
                }
                else {
                    cout << "Huy sua.\n";
                }
            }
            else {
                danhSachGV.push_back(gv);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay giao vien voi MGV: " << mgv << endl;
        }
        else {
            ofstream outFile("GiaoVien.txt");
            for (const auto& g : danhSachGV) {
                outFile << g.MGV << "|" << g.TenGV << "|" << g.MonDay << "|" << g.SDT << endl;
            }
            outFile.close();
        }
    }
    else {
        cout << "Khong the mo file GiaoVien.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm cập nhật dữ liệu điểm
void suaDiem() {
    string maHS, maMH;
    cout << "Nhap MaHS: ";
    getline(cin, maHS);
    cout << "Nhap MaMH: ";
    getline(cin, maMH);

    vector<Diem> danhSachDiem;
    ifstream inFile("BangDiem.txt");
    bool found = false;
    Diem diem;

    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string temp;
            getline(ss, diem.MaHS, '|');
            getline(ss, diem.MaMH, '|');
            ss >> diem.DM; ss.ignore();
            ss >> diem.DCC; ss.ignore();
            ss >> diem.DKT; ss.ignore();
            ss >> diem.DT;

            if (diem.MaHS == maHS && diem.MaMH == maMH) {
                found = true;
                cout << "Thong tin diem hien tai:\n";
                cout << "MaHS: " << diem.MaHS << ", MaMH: " << diem.MaMH << ", DM: " << diem.DM
                    << ", DCC: " << diem.DCC << ", DKT: " << diem.DKT << ", DT: " << diem.DT << endl;

                cout << "Nhap thong tin moi:\n";
                cout << "Nhap DM: ";
                cin >> diem.DM;
                cout << "Nhap DCC: ";
                cin >> diem.DCC;
                cout << "Nhap DKT: ";
                cin >> diem.DKT;
                cout << "Nhap DT: ";
                cin >> diem.DT;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                if (confirmAction("sua diem nay")) {
                    danhSachDiem.push_back(diem);
                    cout << "Da sua diem thanh cong.\n";
                }
                else {
                    cout << "Huy sua.\n";
                }
            }
            else {
                danhSachDiem.push_back(diem);
            }
        }
        inFile.close();

        if (!found) {
            cout << "Khong tim thay diem voi MaHS: " << maHS << " va MaMH: " << maMH << endl;
        }
        else {
            ofstream outFile("BangDiem.txt");
            for (const auto& d : danhSachDiem) {
                outFile << d.MaHS << "|" << d.MaMH << "|" << d.DM << "|" << d.DCC << "|" << d.DKT << "|" << d.DT << endl;
            }
            outFile.close();
        }
    }
    else {
        cout << "Khong the mo file BangDiem.txt de doc.\n";
    }
    cout << "Nhan Enter de tiep tuc...";
    cin.get();
}

// Hàm quản lý sinh viên
void quanLyHocSinh() {
    int choice;
    while (true) {
        displaySubMenu("Sinh Vien");
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
            case 1:
                system("cls");
                themHocSinh();
                system("cls");
                break;
            case 2:
                system("cls");
                suaHocSinh();
                system("cls");
                break;
            case 3:
                system("cls");
                xoaHocSinh();
                system("cls");
                break;
            case 4:
                system("cls");
                return;
            default:
                system("cls");
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
                system("cls");
            }
        }
        else {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap so.\n";
            cout << "Nhan Enter de tiep tuc...";
            cin.get();
            system("cls");
        }
    }
}

// Hàm quản lý giáo viên
void quanLyGiaoVien() {
    int choice;
    while (true) {
        displaySubMenu("Giao Vien");
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
            case 1:
                system("cls");
                themGiaoVien();
                system("cls");
                break;
            case 2:
                system("cls");
                suaGiaoVien();
                system("cls");
                break;
            case 3:
                system("cls");
                xoaGiaoVien();
                system("cls");
                break;
            case 4:
                system("cls");
                return;
            default:
                system("cls");
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
                system("cls");
            }
        }
        else {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap so.\n";
            cout << "Nhan Enter de tiep tuc...";
            cin.get();
            system("cls");
        }
    }
}

// Hàm quản lý điểm
void quanLyDiem() {
    int choice;
    while (true) {
        displaySubMenu("Bang Diem");
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
            case 1:
                system("cls");
                themDiem();
                system("cls");
                break;
            case 2:
                system("cls");
                suaDiem();
                system("cls");
                break;
            case 3:
                system("cls");
                xoaDiem();
                system("cls");
                break;
            case 4:
                system("cls");
                return;
            default:
                system("cls");
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
                system("cls");
            }
        }
        else {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap so.\n";
            cout << "Nhan Enter de tiep tuc...";
            cin.get();
            system("cls");
        }
    }
}

// Hàm chính
int main() {
    int choice;
    while (true) {
        displayMainMenu();
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
            case 1:
                system("cls");
                quanLyHocSinh();
                system("cls");
                break;
            case 2:
                system("cls");
                quanLyGiaoVien();
                system("cls");
                break;
            case 3:
                system("cls");
                quanLyDiem();
                system("cls");
                break;
            case 4:
                system("cls");
                cout << "Thoat chuong trinh.\n";
                return 0;
            default:
                system("cls");
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
                system("cls");
            }
        }
        else {
            system("cls");
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap so.\n";
            cout << "Nhan Enter de tiep tuc...";
            cin.get();
            system("cls");
        }
    }
    return 0;
}
