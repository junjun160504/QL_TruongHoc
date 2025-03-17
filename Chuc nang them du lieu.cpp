#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>
#include <limits>

using namespace std;

// Định nghĩa các lớp
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

class BangDiem {
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
        return round((DM + DCC + DKT * 2 + DT * 3) / 7 * 100) / 100;
    }
    void xuatDiem() const {
        cout << left << setfill(' ') << setw(10) << maHS << setw(10) << maMH << setw(8) << DM
            << setw(8) << DCC << setw(8) << DKT << setw(8) << DT
            << setw(8) << diemTB() << endl;
    }
};

// Đọc dữ liệu từ file Giáo viên
vector<GiaoVien> docGiaoVienTuFile(const string& tenFile) {
    vector<GiaoVien> dsgv;
    ifstream filein(tenFile);
    if (!filein) {
        cout << "Khong the mo file " << tenFile << "!" << endl;
        return dsgv;
    }
    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        GiaoVien gv;
        getline(ss, gv.maGV, '|');
        getline(ss, gv.tenGV, '|');
        getline(ss, gv.monDay, '|');
        getline(ss, gv.sdt, '|');
        dsgv.push_back(gv);
    }
    filein.close();
    return dsgv;
}

// Đọc dữ liệu từ file Học sinh
vector<HocSinh> docHocSinhTuFile(const string& tenFile) {
    vector<HocSinh> dshs;
    ifstream filein(tenFile);
    if (!filein) {
        cout << "Khong the mo file " << tenFile << "!" << endl;
        return dshs;
    }
    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        HocSinh hs;
        getline(ss, hs.maHS, '|');
        getline(ss, hs.tenHS, '|');
        getline(ss, hs.lop, '|');
        getline(ss, hs.diaChi, '|');
        getline(ss, hs.sdt, '|');
        getline(ss, hs.sdtPH, '|');
        dshs.push_back(hs);
    }
    filein.close();
    return dshs;
}

// Đọc dữ liệu từ file Bảng điểm
vector<BangDiem> docBangDiemTuFile(const string& tenFile) {
    vector<BangDiem> dsbd;
    ifstream filein(tenFile);
    if (!filein) {
        cout << "Khong the mo file " << tenFile << "!" << endl;
        return dsbd;
    }
    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        BangDiem bd;
        getline(ss, bd.maHS, '|');
        getline(ss, bd.maMH, '|');
        ss >> bd.DM; ss.ignore();
        ss >> bd.DCC; ss.ignore();
        ss >> bd.DKT; ss.ignore();
        ss >> bd.DT;
        dsbd.push_back(bd);
    }
    filein.close();
    return dsbd;
}

// Ghi file Giáo viên
void ghiFileGV(const string& tenFile, const vector<GiaoVien>& dsgv) {
    ofstream fileout(tenFile);
    for (const auto& gv : dsgv) {
        fileout << gv.maGV << "|" << gv.tenGV << "|" << gv.monDay << "|" << gv.sdt << endl;
    }
    fileout.close();
}

// Ghi file Học sinh
void ghiFileHS(const string& tenFile, const vector<HocSinh>& dshs) {
    ofstream fileout(tenFile);
    for (const auto& hs : dshs) {
        fileout << hs.maHS << "|" << hs.tenHS << "|" << hs.lop << "|"
            << hs.diaChi << "|" << hs.sdt << "|" << hs.sdtPH << endl;
    }
    fileout.close();
}

// Ghi file Bảng điểm
void ghiFileBD(const string& tenFile, const vector<BangDiem>& dsbd) {
    ofstream fileout(tenFile);
    for (const auto& bd : dsbd) {
        fileout << bd.maHS << "|" << bd.maMH << "|" << bd.DM << "|" << bd.DCC << "|" << bd.DKT << "|" << bd.DT << endl;
    }
    fileout.close();
}

// Hàm xác nhận hành động
bool confirmAction() {
    string confirm;
    cout << "Ban co chac chan voi thao tac nay? (y/n): ";
    getline(cin, confirm);
    while (confirm.empty() || (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N")) {
        cout << "Vui long nhap 'y' hoac 'n': ";
        getline(cin, confirm);
    }
    return (confirm == "y" || confirm == "Y");
}

// Hàm hiển thị submenu cho thêm, sửa, xóa
void displaySubMenu(const string& entity) {
    cout << "Quan ly " << entity << ":\n";
    cout << "1. Them du lieu\n";
    cout << "2. Sua du lieu\n";
    cout << "3. Xoa du lieu\n";
    cout << "4. Quay lai\n";
    cout << "Chon chuc nang: ";
}

// Menu chính
void menu() {
    cout << "\n========================= MENU =========================" << endl;
    cout << "| 1. Quan ly sinh vien                                |" << endl;
    cout << "| 2. Quan ly giao vien                                |" << endl;
    cout << "| 3. Quan ly diem                                     |" << endl;
    cout << "| 4. In danh sach giao vien                           |" << endl;
    cout << "| 5. In danh sach sinh vien                           |" << endl;
    cout << "| 6. In danh sach diem theo sinh vien                 |" << endl;
    cout << "| 7. In danh sach diem theo mon                       |" << endl;
    cout << "| 8. Bao cao ket qua hoc tap theo lop                 |" << endl;
    cout << "| 9. In danh sach diem trung binh cua sinh vien       |" << endl;
    cout << "| 10. Hien thi sinh vien co diem trung binh cao nhat  |" << endl;
    cout << "| 11. Tim kiem                                        |" << endl;
    cout << "| 12. Xep loai hoc luc                                |" << endl;
    cout << "| 0. Thoat                                            |" << endl;
    cout << "========================================================" << endl;
    cout << "Chon chuc nang: ";
}

void pauseAndClear() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Hàm sửa dữ liệu học sinh
void suaHocSinh(vector<HocSinh>& dshs) {
    string maHS;
    cout << "Nhap MaHS can sua: ";
    cin >> maHS;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (auto& hs : dshs) {
        if (hs.maHS == maHS) {
            found = true;
            cout << "Thong tin hoc sinh hien tai:\n";
            hs.xuatHS();

            cout << "Nhap thong tin moi:\n";
            cout << "Nhap ten hoc sinh: "; getline(cin, hs.tenHS);
            cout << "Nhap lop: "; cin >> hs.lop;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap dia chi: "; getline(cin, hs.diaChi);
            cout << "Nhap so dien thoai: "; cin >> hs.sdt;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap so dien thoai phu huynh: "; cin >> hs.sdtPH;

            if (confirmAction()) {
                cout << "Da sua hoc sinh thanh cong.\n";
                ghiFileHS("HocSinh.txt", dshs);
            }
            else {
                cout << "Huy sua.\n";
            }
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay hoc sinh voi MaHS: " << maHS << endl;
    }
    pauseAndClear();
}

// Hàm xóa dữ liệu học sinh
void xoaHocSinh(vector<HocSinh>& dshs) {
    string maHS;
    cout << "Nhap MaHS can xoa: ";
    cin >> maHS;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<HocSinh> newList;
    bool found = false;
    for (const auto& hs : dshs) {
        if (hs.maHS == maHS) {
            found = true;
            cout << "Thong tin hoc sinh:\n";
            hs.xuatHS();
            if (!confirmAction()) {
                newList.push_back(hs);
            }
        }
        else {
            newList.push_back(hs);
        }
    }
    if (!found) {
        cout << "Khong tim thay hoc sinh voi MaHS: " << maHS << endl;
    }
    else {
        dshs = newList;
        ghiFileHS("HocSinh.txt", dshs);
        cout << "Da xoa hoc sinh thanh cong.\n";
    }
    pauseAndClear();
}

// Hàm sửa dữ liệu giáo viên
void suaGiaoVien(vector<GiaoVien>& dsgv) {
    string maGV;
    cout << "Nhap MaGV can sua: ";
    cin >> maGV;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (auto& gv : dsgv) {
        if (gv.maGV == maGV) {
            found = true;
            cout << "Thong tin giao vien hien tai:\n";
            gv.xuatGV();

            cout << "Nhap thong tin moi:\n";
            cout << "Nhap ten giao vien: "; getline(cin, gv.tenGV);
            cout << "Nhap mon day: "; getline(cin, gv.monDay);
            cout << "Nhap so dien thoai: "; cin >> gv.sdt;

            if (confirmAction()) {
                cout << "Da sua giao vien thanh cong.\n";
                ghiFileGV("GiaoVien.txt", dsgv);
            }
            else {
                cout << "Huy sua.\n";
            }
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay giao vien voi MaGV: " << maGV << endl;
    }
    pauseAndClear();
}

// Hàm xóa dữ liệu giáo viên
void xoaGiaoVien(vector<GiaoVien>& dsgv) {
    string maGV;
    cout << "Nhap MaGV can xoa: ";
    cin >> maGV;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<GiaoVien> newList;
    bool found = false;
    for (const auto& gv : dsgv) {
        if (gv.maGV == maGV) {
            found = true;
            cout << "Thong tin giao vien:\n";
            gv.xuatGV();
            if (!confirmAction()) {
                newList.push_back(gv);
            }
        }
        else {
            newList.push_back(gv);
        }
    }
    if (!found) {
        cout << "Khong tim thay giao vien voi MaGV: " << maGV << endl;
    }
    else {
        dsgv = newList;
        ghiFileGV("GiaoVien.txt", dsgv);
        cout << "Da xoa giao vien thanh cong.\n";
    }
    pauseAndClear();
}

// Hàm sửa dữ liệu điểm
void suaBangDiem(vector<BangDiem>& dsbd) {
    string maHS, maMH;
    cout << "Nhap MaHS: ";
    cin >> maHS;
    cout << "Nhap MaMH: ";
    cin >> maMH;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found = false;
    for (auto& bd : dsbd) {
        if (bd.maHS == maHS && bd.maMH == maMH) {
            found = true;
            cout << "Thong tin diem hien tai:\n";
            bd.xuatDiem();

            cout << "Nhap thong tin moi:\n";
            cout << "Nhap diem mieng: "; cin >> bd.DM;
            cout << "Nhap diem 15 phut: "; cin >> bd.DCC;
            cout << "Nhap diem kiem tra: "; cin >> bd.DKT;
            cout << "Nhap diem thi: "; cin >> bd.DT;

            if (confirmAction()) {
                cout << "Da sua diem thanh cong.\n";
                ghiFileBD("BangDiem.txt", dsbd);
            }
            else {
                cout << "Huy sua.\n";
            }
            break;
        }
    }
    if (!found) {
        cout << "Khong tim thay diem voi MaHS: " << maHS << " va MaMH: " << maMH << endl;
    }
    pauseAndClear();
}

// Hàm xóa dữ liệu điểm
void xoaBangDiem(vector<BangDiem>& dsbd) {
    string maHS, maMH;
    cout << "Nhap MaHS: ";
    cin >> maHS;
    cout << "Nhap MaMH: ";
    cin >> maMH;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<BangDiem> newList;
    bool found = false;
    for (const auto& bd : dsbd) {
        if (bd.maHS == maHS && bd.maMH == maMH) {
            found = true;
            cout << "Thong tin diem:\n";
            bd.xuatDiem();
            if (!confirmAction()) {
                newList.push_back(bd);
            }
        }
        else {
            newList.push_back(bd);
        }
    }
    if (!found) {
        cout << "Khong tim thay diem voi MaHS: " << maHS << " va MaMH: " << maMH << endl;
    }
    else {
        dsbd = newList;
        ghiFileBD("BangDiem.txt", dsbd);
        cout << "Da xoa diem thanh cong.\n";
    }
    pauseAndClear();
}

// Hàm quản lý học sinh
void quanLyHocSinh(vector<HocSinh>& dshs) {
    int choice;
    while (true) {
        displaySubMenu("Sinh Vien");
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer sau khi nhập choice
        switch (choice) {
        case 1: {
            int soLuong;
            cout << "Nhap so luong hoc sinh: ";
            cin >> soLuong;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer sau khi nhập số lượng
            for (int i = 0; i < soLuong; i++) {
                HocSinh hs;
                cout << "Nhap thong tin hoc sinh thu " << i + 1 << ":" << endl;
                hs.nhapHS();
                dshs.push_back(hs);
            }
            if (confirmAction()) {
                ghiFileHS("HocSinh.txt", dshs);
                cout << "Da them thanh cong!" << endl;
            }
            else {
                cout << "Huy luu du lieu.\n";
                dshs.clear(); // Xóa dữ liệu nếu không lưu
            }
            pauseAndClear();
            break;
        }
        case 2:
            suaHocSinh(dshs);
            break;
        case 3:
            xoaHocSinh(dshs);
            break;
        case 4:
            return;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            break;
        }
    }
}

// Hàm quản lý giáo viên
void quanLyGiaoVien(vector<GiaoVien>& dsgv) {
    int choice;
    while (true) {
        displaySubMenu("Giao Vien");
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1: {
            int soLuong;
            cout << "Nhap so luong giao vien: ";
            cin >> soLuong;
            cin.ignore();
            for (int i = 0; i < soLuong; i++) {
                GiaoVien gv;
                cout << "Nhap thong tin giao vien thu " << i + 1 << ":" << endl;
                gv.nhapGV();
                dsgv.push_back(gv);
            }
            if (confirmAction()) {
                ghiFileGV("GiaoVien.txt", dsgv);
                cout << "Da them thanh cong!" << endl;
            }
            pauseAndClear();
            break;
        }
        case 2:
            suaGiaoVien(dsgv);
            break;
        case 3:
            xoaGiaoVien(dsgv);
            break;
        case 4:
            return;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            break;
        }
    }
}

// Hàm quản lý điểm
void quanLyDiem(vector<HocSinh>& dshs, vector<BangDiem>& dsbd) {
    int choice;
    while (true) {
        displaySubMenu("Bang Diem");
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer sau khi nhập choice
        switch (choice) {
        case 1: {
            dshs = docHocSinhTuFile("HocSinh.txt");
            if (dshs.empty()) {
                cout << "Danh sach hoc sinh dang trong!\n";
                pauseAndClear();
                break;
            }

            // Nhập mã học sinh cần thêm điểm
            string maHS;
            cout << "Nhap ma hoc sinh can them diem: ";
            cin >> maHS;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer

            // Tìm học sinh theo mã
            bool found = false;
            HocSinh hs;
            for (const auto& h : dshs) {
                if (h.maHS == maHS) {
                    hs = h;
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Khong tim thay hoc sinh voi MaHS: " << maHS << endl;
                pauseAndClear();
                break;
            }

            // Nhập mã môn học và điểm cho học sinh đó
            string maMH;
            cout << "Nhap ma mon hoc can nhap diem: ";
            cin >> maMH;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer

            BangDiem bd;
            cout << "Nhap diem cho hoc sinh " << hs.maHS << " - " << hs.tenHS << ": " << endl;
            bd.maHS = hs.maHS;
            bd.maMH = maMH;
            cout << "Nhap diem mieng: "; cin >> bd.DM;
            cout << "Nhap diem 15 phut: "; cin >> bd.DCC;
            cout << "Nhap diem kiem tra: "; cin >> bd.DKT;
            cout << "Nhap diem thi: "; cin >> bd.DT;
            dsbd.push_back(bd);

            if (confirmAction()) {
                ghiFileBD("BangDiem.txt", dsbd);
                cout << "Da them thanh cong!" << endl;
            }
            else {
                cout << "Huy luu du lieu.\n";
                dsbd.pop_back(); // Xóa bản ghi vừa thêm nếu không lưu
            }
            pauseAndClear();
            break;
        }
        case 2:
            suaBangDiem(dsbd);
            break;
        case 3:
            xoaBangDiem(dsbd);
            break;
        case 4:
            return;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            break;
        }
    }
}

int main() {
    vector<HocSinh> dshs;
    vector<GiaoVien> dsgv;
    vector<BangDiem> dsbd;
    int chon;

    do {
        menu();
        cin >> chon;
        cin.ignore();
        switch (chon) {
        case 1: // Quan ly sinh vien
            quanLyHocSinh(dshs);
            break;

        case 2: // Quan ly giao vien
            quanLyGiaoVien(dsgv);
            break;

        case 3: // Quan ly diem
            quanLyDiem(dshs, dsbd);
            break;

        case 4: // In danh sach giao vien
        {
            dsgv = docGiaoVienTuFile("GiaoVien.txt");
            if (dsgv.empty()) {
                cout << "Khong co du lieu giao vien!\n";
                break;
            }
            sort(dsgv.begin(), dsgv.end(), [](const GiaoVien& a, const GiaoVien& b) {
                return a.tenGV < b.tenGV;
                });
            cout << "\n=========== DANH SACH GIAO VIEN ===========\n";
            cout << left << setw(10) << "Ma GV" << setw(20) << "Ten GV" << setw(15) << "Mon day" << setw(15) << "SDT" << endl;
            for (const auto& gv : dsgv) {
                gv.xuatGV();
            }
            pauseAndClear();
            break;
        }

        case 5: // In danh sach sinh vien
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            if (dshs.empty()) {
                cout << "Khong co du lieu hoc sinh!\n";
                break;
            }
            sort(dshs.begin(), dshs.end(), [](const HocSinh& a, const HocSinh& b) {
                return a.tenHS < b.tenHS;
                });
            cout << "\n=========== DANH SACH HOC SINH ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(20) << "Dia chi" << setw(15) << "SDT" << setw(15) << "SDT PH" << endl;
            for (const auto& hs : dshs) {
                hs.xuatHS();
            }
            pauseAndClear();
            break;
        }

        case 6: // In danh sach diem theo sinh vien
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
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
            cout << "\n=========== BANG DIEM CUA HOC SINH " << hs.tenHS << " ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(10) << "Ma MH" << setw(8) << "Diem M" << setw(8) << "Diem TX" << setw(8) << "Diem KT" << setw(8) << "Diem Thi" << setw(8) << "Diem TB" << endl;
            for (const auto& bd : dsbd) {
                if (bd.maHS == maHS) {
                    bd.xuatDiem();
                }
            }
            pauseAndClear();
            break;
        }

        case 7: // In danh sach diem theo mon
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
            if (dshs.empty() || dsbd.empty()) {
                cout << "Khong co du lieu!\n";
                break;
            }
            string maMH;
            cout << "Nhap ma mon hoc: ";
            cin >> maMH;
            cout << "\n=========== BANG DIEM MON " << maMH << " ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(8) << "Diem M" << setw(8) << "Diem TX" << setw(8) << "Diem KT" << setw(8) << "Diem Thi" << setw(8) << "Diem TB" << endl;
            for (const auto& bd : dsbd) {
                if (bd.maMH == maMH) {
                    for (const auto& hs : dshs) {
                        if (hs.maHS == bd.maHS) {
                            cout << left << setw(10) << bd.maHS << setw(20) << hs.tenHS;
                            cout << setw(8) << bd.DM << setw(8) << bd.DCC << setw(8) << bd.DKT << setw(8) << bd.DT << setw(8) << bd.diemTB() << endl;
                        }
                    }
                }
            }
            pauseAndClear();
            break;
        }

        case 8: // Bao cao ket qua hoc tap theo lop
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
            if (dshs.empty() || dsbd.empty()) {
                cout << "Khong co du lieu!\n";
                break;
            }
            string lop;
            cout << "Nhap lop: ";
            cin >> lop;
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
            map<string, bool> monHocMap;
            vector<string> dsMonHoc;
            for (const auto& bd : dsbd) {
                if (!monHocMap[bd.maMH]) {
                    dsMonHoc.push_back(bd.maMH);
                    monHocMap[bd.maMH] = true;
                }
            }
            cout << "\n=========== BAO CAO KET QUA HOC TAP - LOP " << lop << " ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS";
            for (const auto& mon : dsMonHoc) {
                cout << setw(8) << mon;
            }
            cout << setw(8) << "Diem TB" << endl;
            for (const auto& hs : hsTheoLop) {
                cout << left << setw(10) << hs.maHS << setw(20) << hs.tenHS;
                float tongDiem = 0;
                int dem = 0;
                for (const auto& mon : dsMonHoc) {
                    float diemTB = 0;
                    for (const auto& bd : dsbd) {
                        if (bd.maHS == hs.maHS && bd.maMH == mon) {
                            diemTB = bd.diemTB();
                            break;
                        }
                    }
                    if (diemTB == 0) {
                        cout << setw(8) << "N/A";
                    }
                    else {
                        cout << setw(8) << diemTB;
                        tongDiem += diemTB;
                        dem++;
                    }
                }
                cout << setw(8) << (dem > 0 ? round((tongDiem / dem) * 100) / 100 : 0) << endl;
            }
            pauseAndClear();
            break;
        }

        case 9: // In danh sach diem trung binh cua sinh vien
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
            if (dshs.empty() || dsbd.empty()) {
                cout << "Khong co du lieu!\n";
                break;
            }
            string lop;
            cout << "Nhap lop: ";
            cin >> lop;
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
            cout << "\n=========== DIEM TRUNG BINH HOC SINH - LOP " << lop << " ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(8) << "Diem TB" << endl;
            for (const auto& hs : hsTheoLop) {
                float tongDiem = 0;
                int soMon = 0;
                for (const auto& bd : dsbd) {
                    if (bd.maHS == hs.maHS) {
                        tongDiem += bd.diemTB();
                        soMon++;
                    }
                }
                float diemTB = (soMon > 0) ? (tongDiem / soMon) : 0;
                cout << left << setw(10) << hs.maHS << setw(20) << hs.tenHS << setw(8) << round(diemTB * 100) / 100 << endl;
            }
            pauseAndClear();
            break;
        }

        case 10: // Hien thi sinh vien co diem trung binh cao nhat
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
            if (dshs.empty() || dsbd.empty()) {
                cout << "Khong co du lieu!\n";
                break;
            }
            float maxDiemTB = 0;
            vector<HocSinh> hsMaxDiemTB;
            for (const auto& hs : dshs) {
                float tongDiem = 0;
                int soMon = 0;
                for (const auto& bd : dsbd) {
                    if (bd.maHS == hs.maHS) {
                        tongDiem += bd.diemTB();
                        soMon++;
                    }
                }
                float diemTB = (soMon > 0) ? (tongDiem / soMon) : 0;
                if (diemTB > maxDiemTB) {
                    maxDiemTB = diemTB;
                    hsMaxDiemTB.clear();
                    hsMaxDiemTB.push_back(hs);
                }
                else if (diemTB == maxDiemTB) {
                    hsMaxDiemTB.push_back(hs);
                }
            }
            cout << "\n=========== HOC SINH CO DIEM TB CAO NHAT ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(8) << "Diem TB" << endl;
            for (const auto& hs : hsMaxDiemTB) {
                cout << left << setw(10) << hs.maHS << setw(20) << hs.tenHS << setw(10) << hs.lop << setw(8) << round(maxDiemTB * 100) / 100 << endl;
            }
            pauseAndClear();
            break;
        }

        case 11: // Tim kiem
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            if (dshs.empty()) {
                cout << "Khong co du lieu hoc sinh!\n";
                break;
            }
            string keyword;
            cout << "Nhap ten hoc sinh can tim: ";
            cin.ignore();
            getline(cin, keyword);
            cout << "\n=========== KET QUA TIM KIEM ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(20) << "Dia chi" << setw(15) << "SDT" << setw(15) << "SDT PH" << endl;
            bool found = false;
            for (const auto& hs : dshs) {
                if (hs.tenHS.find(keyword) != string::npos) {
                    hs.xuatHS();
                    found = true;
                }
            }
            if (!found) {
                cout << "Khong tim thay hoc sinh nao voi ten " << keyword << "!\n";
            }
            pauseAndClear();
            break;
        }

        case 12: // Xep loai hoc luc
        {
            dshs = docHocSinhTuFile("HocSinh.txt");
            dsbd = docBangDiemTuFile("BangDiem.txt");
            if (dshs.empty() || dsbd.empty()) {
                cout << "Khong co du lieu!\n";
                break;
            }
            string lop;
            cout << "Nhap lop: ";
            cin >> lop;
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
            cout << "\n=========== XEP LOAI HOC LUC - LOP " << lop << " ===========\n";
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(8) << "Diem TB" << setw(12) << "Hoc luc" << endl;
            for (const auto& hs : hsTheoLop) {
                float tongDiem = 0;
                int soMon = 0;
                for (const auto& bd : dsbd) {
                    if (bd.maHS == hs.maHS) {
                        tongDiem += bd.diemTB();
                        soMon++;
                    }
                }
                float diemTB = (soMon > 0) ? (tongDiem / soMon) : 0;
                string hocLuc;
                if (diemTB >= 9) hocLuc = "Xuat sac";
                else if (diemTB >= 8) hocLuc = "Gioi";
                else if (diemTB >= 6.5) hocLuc = "Kha";
                else if (diemTB >= 5) hocLuc = "Trung binh";
                else hocLuc = "Yeu";
                cout << left << setw(10) << hs.maHS << setw(20) << hs.tenHS << setw(8) << round(diemTB * 100) / 100 << setw(12) << hocLuc << endl;
            }
            pauseAndClear();
            break;
        }

        case 0: // Thoat
            cout << "Tam biet!\n";
            break;

        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            break;
        }
    } while (chon != 0);

    return 0;
}
