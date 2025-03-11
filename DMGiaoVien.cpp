#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath> //thư viện để làm tròn

using namespace std;

// Lớp Học Sinh
class HocSinh {
public:
    string maHS, tenHS, lop;
};

// Lớp Bảng Điểm
class BangDiem {
public:
    string maHS, maMH;
    float DM, DCC, DKT, DT;

    float diemTB() const {
        return round((DM + DCC + DKT * 2 + DT * 3) / 7 * 100) / 100; // Làm tròn đến 2 số thập phân
    }
};

// Hàm đọc dữ liệu học sinh từ file
vector<HocSinh> docHocSinhTuFile(const string& tenFile) {
    vector<HocSinh> dshs;
    ifstream filein(tenFile);
    if (!filein) {
        cout << "Khong the mo file " << tenFile << "!\n";
        return dshs;
    }
    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        HocSinh hs;
        getline(ss, hs.maHS, ',');
        getline(ss, hs.tenHS, ',');
        getline(ss, hs.lop, ',');
        dshs.push_back(hs);
    }
    filein.close();
    return dshs;
}

// Hàm đọc dữ liệu bảng điểm từ file
vector<BangDiem> docBangDiemTuFile(const string& tenFile) {
    vector<BangDiem> dsbd;
    ifstream filein(tenFile);
    if (!filein) {
        cout << "Khong the mo file " << tenFile << "!\n";
        return dsbd;
    }
    string line;
    while (getline(filein, line)) {
        stringstream ss(line);
        BangDiem bd;
        getline(ss, bd.maHS, ',');
        getline(ss, bd.maMH, ',');
        string temp;
        getline(ss, temp, ','); bd.DM = stof(temp);
        getline(ss, temp, ','); bd.DCC = stof(temp);
        getline(ss, temp, ','); bd.DKT = stof(temp);
        getline(ss, temp, ','); bd.DT = stof(temp);
        dsbd.push_back(bd);
    }
    filein.close();
    return dsbd;
}

// Hàm tìm và hiển thị học sinh có điểm trung bình cao nhất
void hienThiHocSinhDiemCaoNhat() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

    if (dsbd.empty()) {
        cout << "Danh sach diem dang trong! Vui long nhap diem truoc.\n";
        return;
    }

    float maxDiemTB = 0;
    vector<BangDiem> hsMaxDiemTB;

    // Tìm điểm trung bình cao nhất
    for (const auto& bd : dsbd) {
        float diemTB = bd.diemTB();
        if (diemTB > maxDiemTB) {
            maxDiemTB = diemTB;
            hsMaxDiemTB.clear();
            hsMaxDiemTB.push_back(bd);
        } else if (diemTB == maxDiemTB) {
            hsMaxDiemTB.push_back(bd);
        }
    }

    // Hiển thị danh sách học sinh có điểm trung bình cao nhất
    cout << "\nHoc sinh co diem trung binh cao nhat (" << maxDiemTB << "):\n";
    cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(8) << "TB" << endl;

    for (const auto& bd : hsMaxDiemTB) {
        // Tìm tên học sinh theo mã HS
        auto it = find_if(dshs.begin(), dshs.end(), [&](const HocSinh& hs) {
            return hs.maHS == bd.maHS;
        });

        string tenHS = (it != dshs.end()) ? it->tenHS : "Unknown";
        string lopHS = (it != dshs.end()) ? it->lop : "Unknown";

        cout << left << setw(10) << bd.maHS << setw(20) << tenHS << setw(10) << lopHS << setw(8) << bd.diemTB() << endl;
    }

    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

// Hàm menu
void menu() {
    cout << "\n========================= MENU =========================" << endl;
    cout << "| 1. Hien thi hoc sinh co diem trung binh cao nhat  |" << endl;
    cout << "| 0. Thoat                                         |" << endl;
    cout << "=====================================================" << endl;
    cout << "Chon chuc nang: ";
}

int main() {
    int chon;
    do {
        menu();
        cin >> chon;
        switch (chon) {
            case 1:
                hienThiHocSinhDiemCaoNhat();
                break;
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (chon != 0);
    return 0;
}