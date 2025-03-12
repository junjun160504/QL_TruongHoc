#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <cmath> //thư viện để làm tròn
#include <map> //thư viện để sử dụng map

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

// Hàm tạo báo cáo kết quả học tập theo lớp
void baoCaoKetQuaHocTapTheoLop() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

    if (dshs.empty() || dsbd.empty()) {
        cout << "Khong co du lieu de bao cao!\n";
        return;
    }

    string lopCanBaoCao;
    cout << "Nhap lop can bao cao: ";
    cin >> lopCanBaoCao;

    // Lọc danh sách học sinh thuộc lớp cần báo cáo
    vector<HocSinh> hsTrongLop;
    for (const auto& hs : dshs) {
        if (hs.lop == lopCanBaoCao) {
            hsTrongLop.push_back(hs);
        }
    }

    if (hsTrongLop.empty()) {
        cout << "Khong co hoc sinh nao trong lop " << lopCanBaoCao << "!\n";
        return;
    }

    // Tạo danh sách môn học (không dùng set)
    map<string, bool> monHocMap;
        vector<string> danhSachMonHoc;

        for (const auto& bd : dsbd) {
            if (!monHocMap[bd.maMH]) { // Nếu môn học chưa có trong danh sách
                danhSachMonHoc.push_back(bd.maMH);
                monHocMap[bd.maMH] = true; // Đánh dấu môn học đã thêm
            }
        }

    // Hiển thị báo cáo
    cout << "\n================================= BAO CAO KET QUA HOC TAP - LOP " << lopCanBaoCao << " =================================\n";
        
    // In tiêu đề cột: Mã HS, Tên HS, sau đó là các môn học
    cout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh";
    for (const auto& mon : danhSachMonHoc) {
        cout << setw(10) << mon;
    }
    cout << "Diem TB" << endl;

    // In dữ liệu điểm của từng học sinh
    for (const auto& hs : hsTrongLop) {
        cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
        float TB = 0;
        int dem = 0;
        for (const auto& mon : danhSachMonHoc) {
            float diemTB = -1; // Giá trị mặc định nếu không có điểm
            for (const auto& bd : dsbd) {
                if (bd.maHS == hs.maHS && bd.maMH == mon) {
                    diemTB = bd.diemTB();
                    break;
                }
            }

            if (diemTB == -1) {
                cout << setw(10) << "N/A"; // Không có điểm
            } else {
                cout << setw(10) << diemTB;
            }
            TB += diemTB;
            dem++;
        }
        cout << round((TB/dem)*100)/100 << endl;
    }
    cout << "===================================================================================================\n";

    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
}

void inDiemTrungBinhHocSinh(const vector<HocSinh>& dshs, const vector<BangDiem>& dsbd, const string& lop) {
    // Lọc học sinh theo lớp
    vector<HocSinh> hsTheoLop;
    for (const auto& hs : dshs) {
        if (hs.lop == lop) {
            hsTheoLop.push_back(hs);
        }
    }

    if (hsTheoLop.empty()) {
        cout << "Khong co hoc sinh nao trong lop " << lop << "!\n";
        return;
    }

    // Tính điểm trung bình cho tất cả các môn của mỗi học sinh trong lớp
    for (const auto& hs : hsTheoLop) {
        float tongDiem = 0;
        int soMon = 0;

        for (const auto& bd : dsbd) {
            if (bd.maHS == hs.maHS) {
                tongDiem += bd.diemTB(); // Thêm điểm môn này vào tổng điểm
                soMon++; // Đếm số môn học có điểm
            }
        }

        // Nếu học sinh có điểm ở ít nhất một môn
        float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1; // Tính điểm trung bình

        cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
        if (diemTB == -1) {
            cout << setw(15) << "N/A" << endl; // Nếu không có điểm nào
        } else {
            cout << setw(15) << round(diemTB * 100) / 100 << endl; // Làm tròn đến 2 chữ số thập phân
        }
    }

    cout << "===================================================================================================\n";
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
            case 2:
                baoCaoKetQuaHocTapTheoLop();
                break;

                case 9: { // In danh sách điểm trung bình của học sinh
                    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
                    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
                
                    if (dshs.empty() || dsbd.empty()) {
                        cout << "Khong co du lieu!\n";
                        break;
                    }
                
                    // Hiển thị báo cáo
                    cout << "\n=================================== DANH SACH DIEM TRUNG BINH HOC SINH ===================================\n";
                    cout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(15) << "Diem TB" << endl;
                
                    // Tính điểm trung bình cho tất cả các môn của mỗi học sinh
                    for (const auto& hs : dshs) {
                        float tongDiem = 0;
                        int soMon = 0;
                
                        for (const auto& bd : dsbd) {
                            if (bd.maHS == hs.maHS) {
                                tongDiem += bd.diemTB(); // Thêm điểm môn này vào tổng điểm
                                soMon++; // Đếm số môn học có điểm
                            }
                        }
                
                        // Nếu học sinh có điểm ở ít nhất một môn
                        float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1; // Tính điểm trung bình nếu có môn học
                
                        cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
                        if (diemTB == -1) {
                            cout << setw(15) << "N/A" << endl; // Nếu không có điểm nào
                        } else {
                            cout << setw(15) << round(diemTB * 100) / 100 << endl; // Làm tròn đến 2 chữ số thập phân
                        }
                    }
                
                    cout << "===================================================================================================\n";
                
                    // Hỏi người dùng có muốn in ra file không
                    char inFile;
                    cout << "Ban co muon luu bao cao vao file? (Y/N): ";
                    cin >> inFile;
                
                    if (inFile == 'Y' || inFile == 'y') {
                        ofstream fileout("DiemTrungBinhHocSinh.txt");
                        // In lại báo cáo vào file
                        fileout << "\n=================================== DANH SACH DIEM TRUNG BINH HOC SINH ===================================\n";
                        fileout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(15) << "Diem TB" << endl;
                
                        // In dữ liệu điểm của từng học sinh vào file
                        for (const auto& hs : dshs) {
                            float tongDiem = 0;
                            int soMon = 0;
                
                            for (const auto& bd : dsbd) {
                                if (bd.maHS == hs.maHS) {
                                    tongDiem += bd.diemTB(); // Thêm điểm môn này vào tổng điểm
                                    soMon++; // Đếm số môn học có điểm
                                }
                            }
                
                            // Tính điểm trung bình của học sinh
                            float diemTB = (soMon > 0) ? (tongDiem / soMon) : -1;
                
                            fileout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS;
                            if (diemTB == -1) {
                                fileout << setw(15) << "N/A" << endl; // Nếu không có điểm nào
                            } else {
                                fileout << setw(15) << round(diemTB * 100) / 100 << endl; // Làm tròn đến 2 chữ số thập phân
                            }
                        }
                        fileout.close();
                        cout << "Bao cao da duoc luu vao file DiemTrungBinhHocSinh.txt\n";
                    }
                
                    break;
                }
                
                
            case 0:
                cout << "Thoat chuong trinh.\n";
                break;
            case 10:
            {
                
            }
            default:
                cout << "Lua chon khong hop le. Vui long chon lai!\n";
        }
    } while (chon != 0);
    return 0;
}