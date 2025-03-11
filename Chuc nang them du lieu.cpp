#include <iostream>
#include <string>
#include <limits>

using namespace std;

// Cấu trúc cho dữ liệu giáo viên
struct GiaoVien {
    string MGV;
    string TenGV;
    string MonDay;
    string SDT;
};

// Cấu trúc cho dữ liệu học sinh
struct HocSinh {
    string MaHS;
    string TenHS;
    string Lop;
    string DiaChi;
    string SDT;
    string SDTPH;
};

// Cấu trúc cho dữ liệu điểm
struct Diem {
    string MaHS;
    string MaMH;
    float DM;
    float DCC;
    float DKT;
    float DT;
    // cột cuối là điểm trung bình à?
};

// Hàm hiển thị menu
void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Nhap du lieu sinh vien\n";
    cout << "2. Nhap du lieu giao vien\n";
    cout << "3. Nhap du lieu diem\n";
    cout << "4. Thoat\n";
    cout << "Chon chuc nang: ";
}

// Hàm nhập dữ liệu giáo viên
void nhapGiaoVien() {
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
    cout << "Nhan Enter de tiep tuc...";
    cin.get(); // Đợi người dùng nhấn Enter
}

// Hàm nhập dữ liệu học sinh
void nhapHocSinh() {
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
    cout << "Nhan Enter de tiep tuc...";
    cin.get(); // Đợi người dùng nhấn Enter
}

// Hàm nhập dữ liệu điểm
void nhapDiem() {
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa bộ đệm
    cout << "Da them diem thanh cong.\n";
    cout << "Nhan Enter de tiep tuc...";
    cin.get(); // Đợi người dùng nhấn Enter
}

// Hàm chính
int main() {
    int choice;
    while (true) {
        system("cls"); // Xóa màn hình
        displayMenu(); // Hiển thị menu
        if (cin >> choice) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            switch (choice) {
            case 1:
                system("cls"); // Xóa màn hình trước khi nhập
                nhapHocSinh();
                break;
            case 2:
                system("cls");
                nhapGiaoVien();
                break;
            case 3:
                system("cls");
                nhapDiem();
                break;
            case 4:
                system("cls"); // Xóa màn hình trước khi thoát
                cout << "Thoat chuong trinh.\n";
                return 0;
            default:
                system("cls"); // Xóa màn hình nếu lựa chọn không hợp lệ
                cout << "Lua chon khong hop le. Vui long chon lai.\n";
                cout << "Nhan Enter de tiep tuc...";
                cin.get();
            }
        }
        else {
            system("cls"); // Xóa màn hình nếu nhập sai
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le. Vui long nhap lai.\n";
            cout << "Nhan Enter de tiep tuc...";
            cin.get();
        }
    }
    return 0;
}
