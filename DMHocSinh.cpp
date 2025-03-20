#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <map>

using namespace std;

// Nhập file
ifstream fileinGV("GiaoVien.txt");
ifstream fileinHS("HocSinh.txt");
ifstream fileinBD("BangDiem.txt");

// lớp Giáo viên
class GiaoVien {
public:
    string maGV, tenGV, monDay, sdt;
    bool tt;

    void nhapGV() {
        cout << "Nhap ma giao vien: "; cin >> maGV;
        cout << "Nhap ten giao vien: "; cin.ignore(); getline(cin, tenGV);
        cout << "Nhap mon day: "; getline(cin, monDay);
        cout << "Nhap so dien thoai: "; cin >> sdt;
        tt = true;
    }

    void xuatGV() const {
        if (tt) {
            cout << left << setfill(' ') << setw(10) << maGV << setw(20) << tenGV
                << setw(15) << monDay << setw(15) << sdt << endl;
        }
    }

    void xoaGV() {
        tt = false;
    }
};

// lớp Học sinh
class HocSinh {
public:
    string maHS, tenHS, lop, diaChi, sdt, sdtPH;
    bool tt;

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
        if (tt) {
            cout << left << setfill(' ') << setw(10) << maHS << setw(20) << tenHS
                << setw(10) << lop << setw(20) << diaChi << setw(15) << sdt << setw(15) << sdtPH << endl;
        }
    }

    void xoaHS() {
        tt = false;
    }
};

// lớp Bảng điểm
class BangDiem {
public:
    string maHS, maMH;
    float DM, DCC, DKT, DT;
    bool tt;

    void nhapDiem() {
        cout << "Nhap ma hoc sinh: "; cin >> maHS;
        cout << "Nhap ma mon hoc: "; cin >> maMH;
        cout << "Nhap diem mieng: "; cin >> DM;
        cout << "Nhap diem 15 phut: "; cin >> DCC;
        cout << "Nhap diem kiem tra: "; cin >> DKT;
        cout << "Nhap diem thi: "; cin >> DT;
        tt = true;
    }

    float diemTB() const {
        return round((DM + DCC + DKT * 2 + DT * 3) / 7 * 100) / 100;
    }

    void xuatDiem() const {
        if (tt) {
            cout << left << setfill(' ') << setw(10) << maHS << setw(10) << maMH
                << setw(8) << DM << setw(8) << DCC << setw(8) << DKT
                << setw(8) << DT << setw(8) << diemTB() << endl;
        }
    }

    void xoaDiem() {
        tt = false;
    }
};

// Đọc dữ liệu từ file
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
        getline(ss, gv.maGV, ',');
        getline(ss, gv.tenGV, ',');
        getline(ss, gv.monDay, ',');
        getline(ss, gv.sdt, ',');
        dsgv.push_back(gv);
    }
    filein.close();
    return dsgv;
}

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
        getline(ss, hs.maHS, ',');
        getline(ss, hs.tenHS, ',');
        getline(ss, hs.lop, ',');
        if (ss.peek() == '"') {
            ss.get();
            getline(ss, hs.diaChi, '"');
            ss.get();
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

// Ghi dữ liệu vào file
void ghiFileGV(const string& tenFile, const vector<GiaoVien>& dsgv) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& gv : dsgv) {
        fileout << gv.maGV << "," << gv.tenGV << "," << gv.monDay << "," << gv.sdt << endl;
    }
    fileout.close();
}

void ghiFileHS(const string& tenFile, const vector<HocSinh>& dshs) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& hs : dshs) {
        fileout << hs.maHS << "," << hs.tenHS << "," << hs.lop << ","
            << hs.diaChi << "," << hs.sdt << "," << hs.sdtPH << endl;
    }
    fileout.close();
}

void ghiFileBD(const string& tenFile, const vector<BangDiem>& dsbd) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& bd : dsbd) {
        fileout << bd.maHS << "," << bd.maMH << "," << bd.DM << "," << bd.DCC << "," << bd.DKT << "," << bd.DT << endl;
    }
    fileout.close();
}

// Hàm tổng quát cho quản lý
template <typename T>
void quanLyDuLieu(vector<T>& ds, const string& entityName,
                  void (*nhap)(T&), void (*sua)(vector<T>&),
                  void (*xoa)(vector<T>&), void (*in)(const vector<T>&),
                  void (*ghi)(const string&, const vector<T>&)) {
    int choice;
    while (true) {
        displaySubMenu(entityName);
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice) {
        case 1: {
            int soLuong;
            cout << "Nhap so luong " << entityName << ": ";
            cin >> soLuong;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int i = 0; i < soLuong; i++) {
                T obj;
                cout << "Nhap thong tin " << entityName << " thu " << i + 1 << ":" << endl;
                nhap(obj);
                ds.push_back(obj);
            }
            if (confirmAction()) {
                ghi(entityName + ".txt", ds);
                cout << "Da them thanh cong!" << endl;
            } else {
                cout << "Huy luu du lieu.\n";
                ds.clear();
            }
            pauseAndClear();
            break;
        }
        case 2:
            sua(ds);
            break;
        case 3:
            xoa(ds);
            break;
        case 4:
            in(ds);
            break;
        case 5:
            return;
        default:
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            break;
        }
    }
}
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
// Hàm hiển thị submenu cho thêm, sửa, xóa, in
void displaySubMenu(const string& entity) {
    cout << "\n==================Quan ly " << entity << "================" << endl;
    cout << "|1. Them du lieu                               |" << endl;
    cout << "|2. Sua du lieu                                |" << endl;
    cout << "|3. Xoa du lieu                                |" << endl;
    cout << "|4. In du lieu                                 |" << endl;
    cout << "============================================" << endl;
    cout << "Chon chuc nang: ";
}

void nhapHocSinh(HocSinh& hs) {
    hs.nhapHS();
}

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

void inDanhSachHocSinh(const vector<HocSinh>& dshs) {
    for (const auto& hs : dshs) {
        hs.xuatHS();
    }
}
void pauseAndClear() {
    cout << "\nNhan Enter de tiep tuc...";
    //system("pause");
    cin.ignore();
    cin.get();
 //   system("cls"); // Xóa màn hình
}
int main() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

    quanLyDuLieu(dshs, "HocSinh", nhapHocSinh, suaHocSinh, xoaHocSinh, inDanhSachHocSinh, ghiFileHS);
    // quanLyDuLieu(dsgv, "GiaoVien", nhapGiaoVien, suaGiaoVien, xoaGiaoVien, inDanhSachGiaoVien, ghiFileGV);
    // quanLyDuLieu(dsbd, "BangDiem", nhapBangDiem, suaBangDiem, xoaBangDiem, inDanhSachBangDiem, ghiFileBD);

    return 0;
}
