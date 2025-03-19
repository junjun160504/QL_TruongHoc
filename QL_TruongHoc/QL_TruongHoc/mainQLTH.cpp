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

//Nhập file
ifstream fileinGV("GiaoVien.txt");
ifstream fileinHS("HocSinh.txt");
ifstream fileinBD("BangDiem.txt");

//lớp Giáo viên
class GiaoVien {
public:
    string maGV, tenGV, monDay, sdt;
    bool tt;
    void nhapGV(string ma) {
        maGV = ma;
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

//lớp Học sinh
class HocSinh {
public:
    string maHS, tenHS, lop, diaChi, sdt, sdtPH;
	bool tt;  

    // Hàm tạo mã học sinh kế tiếp (tăng dần)
    void nhapHS(string ma) {
        maHS = ma;
        cout << "Nhap ten hoc sinh: "; cin.ignore(); getline(cin, tenHS);
        cout << "Nhap lop: "; cin >> lop; //cin.ignore(); getline(cin, lop);
        cout << "Nhap dia chi: "; cin.ignore(); getline(cin, diaChi);
        cout << "Nhap so dien thoai: "; cin >> sdt;
        cout << "Nhap so dien thoai phu huynh: "; cin >> sdtPH;
		tt = true;
    }
    void xuatHS() const {
		if (tt) {
            cout << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(20) << "Dia Chi"
                << setw(15) << "So DT" << setw(15) << "SDT PH"  << endl;
            cout << "----------------------------------------------------------------------------------\n";
            cout << left << setfill(' ') << setw(10) << maHS << setw(20) << tenHS 
                << setw(10) << lop << setw(20) << diaChi << setw(15) << sdt << setw(15) << sdtPH << endl;
		}
    }
    void xoaHS() {
        tt = false;
    }
};

//lớp Bảng điểm
class BangDiem : public HocSinh, public GiaoVien {
public:
	string maMH, maHS_D;
    float DM, DCC, DKT, DT;
	bool tt;

    void nhapDiem() {
        //HocSinh::nhapHS(dshs); // Nhập thông tin học sinh
		//GiaoVien::nhapGV(); // Nhập thông tin giáo viên
        maHS_D = maHS;
        maMH = monDay; // Mã môn học sẽ được lấy từ môn dạy của giáo viên
        cout << "Nhap diem mieng: "; cin >> DM;
        cout << "Nhap diem 15 phut: "; cin >> DCC;
        cout << "Nhap diem kiem tra: "; cin >> DKT;
        cout << "Nhap diem thi: "; cin >> DT;
		tt = true;
    }
    float diemTB() const {
        return round((DM + DCC + DKT * 2 + DT * 3) / 7 * 100) / 100; //làm tròn đến 2 số thập phân
    }
    void xuatDiem() const {
        if (tt) {
            cout << left << setfill(' ') << setw(10) << maHS << setw(10) << monDay  // Môn học từ giáo viên
                << setw(8) << DM << setw(8) << DCC << setw(8) << DKT
                << setw(8) << DT << setw(8) << diemTB() << endl;
            // Hiển thị thông tin học sinh và giáo viên
            HocSinh::xuatHS();
            GiaoVien::xuatGV();
        }
    }
    void xoaDiem() {
        tt = false;
    }
};

// Hàm xác nhận hành động
bool confirmAction() {
    string confirm;
    cout << endl;
    cout << "Ban co chac chan voi thao tac nay? (y/n): ";
    getline(cin, confirm);
    while (confirm.empty() || (confirm != "y" && confirm != "Y" && confirm != "n" && confirm != "N")) {
        getline(cin, confirm);
    }
    return (confirm == "y" || confirm == "Y");
}

void pauseAndClear() {
    cout << "\nNhan Enter de tiep tuc...";
    cin.ignore();
    cin.get();
    system("cls"); // Xóa màn hình
}

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
        int tt;  // Đọc trạng thái tt (0 hoặc 1)
        ss >> tt;  // Đọc giá trị tt
        gv.tt = (tt == 1);  // Chuyển tt thành kiểu bool
        if (gv.tt) {
            dsgv.push_back(gv);
        }

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
    while (getline(filein, line)) { 
        stringstream ss(line); 
        HocSinh hs;
        getline(ss, hs.maHS, ',');
        getline(ss, hs.tenHS, ',');
        getline(ss, hs.lop, ',');
        if (ss.peek() == '"') { // Kiểm tra nếu địa chỉ bắt đầu bằng dấu "
            ss.get(); // Bỏ qua dấu "
            getline(ss, hs.diaChi, '"'); // Đọc đến dấu " tiếp theo
            ss.get(); // Bỏ qua dấu , sau dấu "
        }
        else {
            getline(ss, hs.diaChi, ',');
        }
        getline(ss, hs.sdt, ',');
        getline(ss, hs.sdtPH, ',');

        int tt;  // Đọc trạng thái tt (0 hoặc 1)
        ss >> tt;  // Đọc giá trị tt
        hs.tt = (tt == 1);  // Chuyển tt thành kiểu bool

        if (hs.tt) {
            dshs.push_back(hs);
        }
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
    while (getline(filein, line)) {
        stringstream ss(line);
        BangDiem bd;
        getline(ss, bd.maHS, ',');
        getline(ss, bd.maMH, ',');
        ss >> bd.DM; ss.ignore();
        ss >> bd.DCC; ss.ignore();
        ss >> bd.DKT; ss.ignore();
        ss >> bd.DT;
        if (bd.tt) {
            dsbd.push_back(bd);
        }
    }
    filein.close();
    return dsbd;
}

// Tạo mã giáo viên
static string taoMaGV() {
    vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
    int maxNum = 0;
    for (const auto& gv : dsgv) {         // Tìm mã giáo viên lớn nhất
        string numPart = gv.maGV.substr(2);  // Giả sử mã giáo viên có định dạng "GVxxx"
        int num = stoi(numPart);  // Chuyển phần số thành số nguyên
        maxNum = max(maxNum, num);  // Tìm số lớn nhất
    }
    int newNum = maxNum + 1;
    char newMa[10];  // Mảng ký tự để lưu mã giáo viên
    sprintf_s(newMa, sizeof(newMa), "GV%03d", newNum);  // Dùng sprintf_s để chuyển số thành chuỗi (phải chỉ định kích thước của mảng) // Chỉ định kích thước mảng newMa
    return string(newMa);  // Chuyển mảng char thành string
}

// Tạo mã học sinh
static string taoMaHS() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    int maxNum = 0;
    for (const auto& hs : dshs) {  // Tìm mã học sinh lớn nhất
        if (hs.maHS.substr(0, 2) == "HS") {
            string numPart = hs.maHS.substr(2);  // Cắt phần số từ mã "HSxxx"
            try {
                int num = stoi(numPart);  // Chuyển phần số thành số nguyên
                maxNum = max(maxNum, num);  // Cập nhật giá trị maxNum nếu tìm thấy số lớn hơn
            }
            catch (const invalid_argument&) {
                cout << "Lỗi: Mã học sinh không hợp lệ: " << hs.maHS << endl;
            }
        }
    }
    int newNum = maxNum + 1;
    char newMa[10];  // Mảng ký tự để lưu mã học sinh
    sprintf_s(newMa, sizeof(newMa), "HS%03d", newNum);  // Dùng sprintf_s để chuyển số thành chuỗi (phải chỉ định kích thước của mảng) // Chỉ định kích thước mảng newMa
    return string(newMa);  // Chuyển mảng char thành string
}

//ghi file Giáo Viên
void ghiFileGV(const string& tenFile, const vector<GiaoVien>& dsgv) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& gv : dsgv) { // duyệt qua từng phần tử trong vector
        if(gv.tt) {
            fileout << gv.maGV << "," << gv.tenGV << "," << gv.monDay << "," << gv.sdt << "," << gv.tt << endl;
        }
    }
    fileout.close();
}

//ghi file Học Sinh
void ghiFileHS(const string& tenFile, const vector<HocSinh>& dshs) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& hs : dshs) { 
        if (hs.tt) {
            fileout << hs.maHS << "," << hs.tenHS << "," << hs.lop << ","
                << "\"" << hs.diaChi << "\"" << "," << hs.sdt << "," << hs.sdtPH << "," << hs.tt << endl;
        }
    }
    fileout.close();
}

//ghi file Bảng Điểm
void ghiFileBD(const string& tenFile, const vector<BangDiem>& dsbd) {
    ofstream fileout(tenFile, ios::app);
    for (const auto& bd : dsbd) { 
        if (bd.tt) {
            fileout << bd.maHS << "," << bd.maMH << "," << bd.DM << "," << bd.DCC << "," << bd.DKT << "," << bd.DT << endl;
        }
    }
    fileout.close();
}

//Sửa file HS
void suaFileHS(const string& tenFile, const vector<HocSinh>& dshs) {
    ofstream fileout(tenFile, ios::out);
    if (!fileout) {
        cout << "Khong the mo file de ghi!" << endl;
        return;
    }
    for (const auto& hs : dshs) {
            fileout << hs.maHS << "," << hs.tenHS << "," << hs.lop << ","
                << "\"" << hs.diaChi << "\"" << "," << hs.sdt << "," << hs.sdtPH << "," << hs.tt << endl;
    }
    fileout.close();
}

//Sửa file GV
void suaFileGV(const string& tenFile, const vector <GiaoVien>& dsgv )
{
	ofstream fileout(tenFile, ios::out);
	if (!fileout) {
		cout << "Khong the mo file de ghi!" << endl;
		return;
	}
	for (const auto& gv : dsgv) {
		if (gv.tt) {
			fileout << gv.maGV << "," << gv.tenGV << "," << gv.monDay << "," << gv.sdt << "," << gv.tt << endl;
		}
	}
	fileout.close();
}

//Sửa file BD
void suaFileBD(const string& tenFile, const vector<BangDiem>& dsbd) {
	ofstream fileout(tenFile, ios::out);
	if (!fileout) {
		cout << "Khong the mo file de ghi!" << endl;
		return;
	}
	for (const auto& bd : dsbd) {
		if (bd.tt) {
			fileout << bd.maHS << "," << bd.maMH << "," << bd.DM << "," << bd.DCC << "," << bd.DKT << "," << bd.DT << endl;
		}
	}
	fileout.close();
}

// Hàm tính điểm trung bình của học sinh
float tinhDiemTB(const string& maHS, const vector<BangDiem>& dsbd) {
    float tongDiem = 0;
    int soMon = 0;

    for (const auto& bd : dsbd) {
        if (bd.tt && bd.maHS == maHS) { // Kiểm tra trạng thái tt của bảng điểm
            tongDiem += bd.diemTB();
            soMon++;
        }
    }

    if (soMon > 0) {
        return round((tongDiem / soMon) * 100) / 100; // Làm tròn đến 2 chữ số thập phân
    }
    else {
        return -1;
    }
}

// Hàm in danh sách học sinh theo lớp
void inDanhSachHocSinh() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    if (dshs.empty()) {
        cout << "Khong co du lieu hoc sinh!\n";
        return;
    }

    // Hàm tách họ, tên đệm, tên chính
    auto splitName = [](const string& fullName) {
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

    // Nhập tên lớp để lọc danh sách học sinh
    string lop;
    cout << "Nhap lop hoc (hoac nhap (all) de hien thi tat ca) : "; cin.ignore(); getline(cin, lop);

    // Sắp xếp danh sách học sinh hợp lệ (tt = true)
    sort(dshs.begin(), dshs.end(), [&](const HocSinh& a, const HocSinh& b) {
        if (!a.tt || !b.tt) return false;  // Bỏ qua học sinh không hợp lệ

        // Tách họ, tên đệm, tên chính
        string hoA, demA, tenA;
        tie(hoA, demA, tenA) = splitName(a.tenHS);  // Giải nén tuple cho học sinh a

        string hoB, demB, tenB;
        tie(hoB, demB, tenB) = splitName(b.tenHS);  // Giải nén tuple cho học sinh b

        if (tenA != tenB) return tenA < tenB;  // Ưu tiên theo tên chính
        if (demA != demB) return demA < demB;  // Nếu tên chính giống nhau, xét tên đệm
        return hoA < hoB;  // Nếu tên chính + tên đệm giống nhau, xét họ
        });

    // Hiển thị danh sách học sinh hợp lệ đã sắp xếp
    cout << "\n=================================================== DANH SACH HOC SINH =========================================================\n" << endl;
    cout << "| " << left << setw(15) << "Ma hoc sinh"
        << setw(20) << "Ten hoc sinh"
        << setw(10) << "Lop"
        << setw(50) << "Dia chi"
        << setw(15) << "SDT"
        << setw(15) << "SDT phu huynh" << "|" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

    bool found = false;
    for (const auto& hs : dshs) {
        if ((lop == "all" || hs.lop == lop) && hs.tt) {  // Kiểm tra học sinh hợp lệ (tt = true)
            cout << "| " << left << setw(15) << hs.maHS
                << setw(20) << hs.tenHS
                << setw(10) << hs.lop
                << setw(50) << hs.diaChi
                << setw(15) << hs.sdt
                << setw(15) << hs.sdtPH << "|" << endl;
            found = true;
        }
    }
    cout << "================================================================================================================================\n";

    if (!found) {
        cout << "Khong co hoc sinh hop le de hien thi!" << endl;
    }

    // Xác nhận lưu danh sách vào file
    char save;
    cout << "Ban co muon luu danh sach vao file? (Y/N): ";
    cin >> save;
    if (tolower(save) == 'y') {
        ofstream fileout("DanhSachHocSinh.txt");
        fileout << "\n=================================================== DANH SACH HOC SINH =========================================================\n" << endl;
        fileout << "| " << left << setw(15) << "Ma hoc sinh"
            << setw(20) << "Ten hoc sinh"
            << setw(10) << "Lop"
            << setw(50) << "Dia chi"
            << setw(15) << "SDT"
            << setw(15) << "SDT phu huynh" << "|" << endl;
        fileout << "--------------------------------------------------------------------------------------------------------------------------------\n";

        // Ghi vào file, chỉ ghi học sinh hợp lệ
        for (const auto& hs : dshs) {
            if ((lop == "all" || hs.lop == lop) && hs.tt) {  // Chỉ ghi học sinh hợp lệ
                string diaChiLuuFile = hs.diaChi;
                if (diaChiLuuFile.find(',') != string::npos) {
                    diaChiLuuFile = '"' + diaChiLuuFile + '"';
                }

                fileout << "| " << left << setw(15) << hs.maHS
                    << setw(20) << hs.tenHS
                    << setw(10) << hs.lop
                    << setw(50) << diaChiLuuFile
                    << setw(15) << hs.sdt
                    << setw(15) << hs.sdtPH << "|" << endl;
            }
        }
        fileout << "================================================================================================================================\n";
        fileout.close();
        cout << "Danh sach da duoc luu vao file DanhSachHocSinh.txt\n";
    }
}

// Hàm hiển thị submenu
void displaySubMenu(const string& entity) {
    cout << "\n==================Quan ly " << entity << "================" << endl;
    cout << "|1. Them du lieu                               |" << endl;
    cout << "|2. Sua du lieu                                |" << endl;
    cout << "|3. Xoa du lieu                                |" << endl;
    cout << "|4. Xem danh sach/ Tim kiem                    |" << endl;
    cout << "|0. Quay lai                                   |" << endl;
    cout << "============================================" << endl;
    cout << "Chon chuc nang: ";
}

// Tìm học sinh theo mã
void timHSTheoMa()
{
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    if (dshs.empty()) {
        cout << "Khong co du lieu de tim kiem!\n";
        return;
    }
    string keyword;
    cout << "Nhap ma de tim kiem: "; cin.ignore(); getline(cin, keyword);
    
    bool foundStudent = false;
    for (const auto& hs : dshs) {
        if (hs.tt && hs.maHS.find(keyword) != string::npos) {
            if (!foundStudent) {
                cout << "\nKet qua tim kiem hoc sinh:\n";
                cout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(10) << "Lop"
                    << setw(50) << "Dia chi" << setw(15) << "SDT" << setw(15) << "SDT phu huynh" << endl;
                foundStudent = true;
            }
            cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS << setw(10) << hs.lop
                << setw(50) << hs.diaChi << setw(15) << hs.sdt << setw(15) << hs.sdtPH << endl;
        }
    }
    if (!foundStudent) {
        cout << "Khong tim thay hoc sinh nao.\n";
    }
}

// Tìm học sinh theo tên
void timHSTheoTen()
{
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    if (dshs.empty()) {
        cout << "Khong co du lieu de tim kiem!\n";
        return;
    }
    string keyword;
    cout << "Nhap ten de tim kiem: "; cin.ignore(); getline(cin, keyword);

    bool foundStudent = false;
    for (const auto& hs : dshs) {
        if (hs.tt && hs.tenHS.find(keyword) != string::npos) {
            if (!foundStudent) {
                cout << "\nKet qua tim kiem hoc sinh:\n";
                cout << left << setw(15) << "Ma hoc sinh" << setw(20) << "Ten hoc sinh" << setw(10) << "Lop"
                    << setw(50) << "Dia chi" << setw(15) << "SDT" << setw(15) << "SDT phu huynh" << endl;
                foundStudent = true;
            }
            cout << left << setw(15) << hs.maHS << setw(20) << hs.tenHS << setw(10) << hs.lop
                << setw(50) << hs.diaChi << setw(15) << hs.sdt << setw(15) << hs.sdtPH << endl;
        }
    }
    if (!foundStudent) {
        cout << "Khong tim thay hoc sinh nao.\n";
    }
}

// Hàm hiển thị submenu cho tìm kiếm
void dptimKiemHS(const string& entity) {
	cout << "\n================Xem / Tim kiem " << entity << "==============" << endl;
    cout << "|1. Xem danh sach hoc sinh theo lop            |" << endl;
	cout << "|2. Tim kiem hoc sinh theo ma                  |" << endl;
	cout << "|3. Tim kiem hoc sinh theo ten                 |" << endl;
    cout << "|0. Quay lai                                   |" << endl;
	cout << "============================================" << endl;
	cout << "Chon chuc nang: ";
}

// Case tìm kiếm
void timKiemHS() {
    system("cls");
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    int chonTK;
    while (true) {
        dptimKiemHS("Hoc Sinh");
        cin >> chonTK;
        switch (chonTK)
        {
            case 1: //Xem danh sach hoc sinh theo lop  
            {
                inDanhSachHocSinh();
                pauseAndClear();
                break;
            };
            case 2: //Tim kiem hoc sinh theo ma
            {
                timHSTheoMa();
                pauseAndClear();
                break;
            };
            case 3: //Tim kiem hoc sinh theo ten
            {
                timHSTheoTen();
                pauseAndClear();
                break;
            };
            case 0: //quay lại
            {
                return;
            };
            default:
            {
                cout << "\nChuc nang khong hop le!" << endl;
                return;
            };
        }
    }
}

// Hàm hiển thị submenu cho sắp xếp
void displaySortMenu(const string& entity) {
	cout << "\n==================Sap xep " << entity << "================" << endl;
	cout << "|1. Sap xep theo ten                           |" << endl;
	cout << "|2. Sap xep theo diem trung binh               |" << endl;
	cout << "============================================" << endl;
	cout << "Chon chuc nang: ";
}

// Hàm hiển thị submenu cho báo cáo
void displayReportMenu() {
	cout << "\n==================Bao cao================" << endl;
	cout << "|1. Bao cao ket qua hoc tap theo lop     |" << endl;
	cout << "|2. In danh sach diem trung binh cua HS  |" << endl;
	cout << "|3. Hien thi HS co diem trung binh cao nhat|" << endl;
	cout << "============================================" << endl;
	cout << "Chon chuc nang: ";
}

// Hàm thêm học sinh vào danh sách
void themHocSinh() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    int soLuong;
    cout << "Nhap so luong hoc sinh: ";
    cin >> soLuong;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Xóa buffer sau khi nhập số lượng
    for (int i = 0; i < soLuong; i++) {
        HocSinh hs;
        cout << "Nhap thong tin hoc sinh thu " << i + 1 << ":" << endl;
        hs.nhapHS(taoMaHS());
        dshs.push_back(hs);
    }
    if (confirmAction()) {
        suaFileHS("HocSinh.txt", dshs);
        cout << "Da them hoc sinh moi!" << endl;
    }
    else {
        cout << "Huy luu du lieu.\n";
        dshs.clear(); // Xóa dữ liệu nếu không lưu
    }
}

// Hàm sửa thông tin học sinh
void suaHocSinh() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    string ma;
    cout << "Nhap ma hoc sinh can sua: "; cin.ignore(); getline(cin, ma);

    // Tìm kiếm học sinh trong danh sách
    bool found = false;
    for (auto& hs : dshs) {
        if (hs.maHS == ma && hs.tt) {  // Kiểm tra học sinh còn hợp lệ (tt = true)
            found = true;
            cout << "\nThong tin hoc sinh hien tai: " << endl;
            hs.xuatHS();  // Hiển thị thông tin học sinh

            int choice;
            cout << "\nBan muon sua thong tin nao?" << endl;
            cout << "1. Sua ten hoc sinh" << endl;
            cout << "2. Sua lop" << endl;
            cout << "3. Sua dia chi" << endl;
            cout << "4. Sua so dien thoai" << endl;
            cout << "5. Sua so dien thoai phu huynh" << endl;
            cout << "Chon chuc nang can sua: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "\nNhap ten hoc sinh moi: "; cin.ignore(); getline(cin, hs.tenHS);  // Chỉ sửa tên học sinh
                break;
            case 2:
                cout << "\nNhap lop moi: "; cin >> hs.lop;  // Chỉ sửa lớp
                break;
            case 3:
                cout << "\nNhap dia chi moi: "; cin.ignore(); getline(cin, hs.diaChi);  // Chỉ sửa địa chỉ
                break;
            case 4:
                cout << "\nNhap so dien thoai moi: "; cin >> hs.sdt;  // Chỉ sửa số điện thoại
                break;
            case 5:
                cout << "\nNhap so dien thoai phu huynh moi: "; cin >> hs.sdtPH;  // Chỉ sửa số điện thoại phụ huynh
                break;
            default:
                cout << "\nChuc nang khong hop le!" << endl;
                return;
            }
            if (confirmAction()) {
                suaFileHS("HocSinh.txt", dshs);
                cout << "Da sua thong tin hoc sinh!" << endl;
            }
            else {
                cout << "Huy sua.\n";
            }
            return;
        }
    }
    if (!found) {
        cout << "Khong tim thay hoc sinh voi MaHS: " << ma << endl;
    }
}

// Hàm xóa học sinh 
void xoaHocSinh() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    string ma;
    cout << "Nhap ma hoc sinh can xoa: "; cin.ignore(); getline(cin, ma);

    // Tìm học sinh trong danh sách
    for (auto& hs : dshs) {
        if (hs.maHS == ma && hs.tt) {
            cout << "\nThong tin hoc sinh can xoa: " << endl;
            hs.xuatHS();

            if (confirmAction()) {
                hs.xoaHS();  // Đánh dấu học sinh này là không hợp lệ (tt = false)
                suaFileHS("HocSinh.txt", dshs);  // Ghi lại danh sách học sinh sau khi xóa vào file
                cout << "Da xoa hoc sinh!" << endl;
            }
            else {
                cout << "Huy xoa.\n";
            }
            return;
        }
    }
    cout << "Hoc sinh khong ton tai!" << endl;
}

// Hàm thêm giáo viên vào danh sách
void themGiaoVien() {
	vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
	GiaoVien gv;    // Tạo đối tượng giáo viên
	gv.nhapGV(taoMaGV());    // Gọi phương thức nhapGV() để nhập thông tin giáo viên
	dsgv.push_back(gv);  // Thêm giáo viên vào danh sách
    if (confirmAction()) {
        ghiFileGV("GiaoVien.txt", dsgv);
        cout << "Da them giao vien moi!" << endl;
    }
    else {
        cout << "Huy luu du lieu.\n";
        dsgv.clear(); // Xóa dữ liệu nếu không lưu
    }
}

// Hàm sửa thông tin giáo viên
void suaGiaoVien() {
	vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
	string ma;
	cout << "Nhap ma giao vien can sua: "; cin >> ma;

	// Tìm kiếm giáo viên trong danh sách
	for (auto& gv : dsgv) {
		if (gv.maGV == ma && gv.tt) { 
			cout << "\nThong tin giao vien hien tai: " << endl;
			gv.xuatGV(); 
			
			int choice;
			cout << "\nBan muon sua thong tin nao?" << endl;
			cout << "1. Sua ten giao vien" << endl;
			cout << "2. Sua mon day" << endl;
			cout << "3. Sua so dien thoai" << endl;
			cout << "Chon chuc nang can sua: ";
			cin >> choice;
			switch (choice) {
			    case 1:
				    cout << "Nhap ten giao vien moi: "; cin.ignore(); getline(cin, gv.tenGV);  // Chỉ sửa tên giáo viên
				    break;
			    case 2:
				    cout << "Nhap mon day moi: "; cin.ignore(); getline(cin, gv.monDay);  // Chỉ sửa môn dạy
				    break;
			    case 3:
				    cout << "Nhap so dien thoai moi: "; cin >> gv.sdt;  // Chỉ sửa số điện thoại
				    break;
			    default:
				    cout << "Chuc nang khong hop le!" << endl;
				    return;
			}
            if (confirmAction()) {
                suaFileGV("GiaoVien.txt", dsgv);
                cout << "Da sua thong tin giao vien!" << endl;
            }
            else {
                cout << "Huy sua.\n";
            }
            return;
		}
	}
	cout << "Giao vien khong ton tai hoac da bi xoa!" << endl;
}

// Hàm xóa giáo viên
void xoaGiaoVien() {
	vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
	string ma;
	cout << "Nhap ma giao vien can xoa: ";
	cin >> ma;

	for (auto& gv : dsgv) {
		if (gv.maGV == ma && gv.tt) { 
			cout << "\nThong tin giao vien can xoa: " << endl;
			gv.xuatGV();
            if (confirmAction()) {
                gv.xoaGV();
                suaFileGV("GiaoVien.txt", dsgv);
                cout << "Da xoa giao vien!" << endl;
            }
            else {
                cout << "Huy xoa.\n";
            }
            return;
		}
	}
	cout << "Giao vien khong ton tai!" << endl;
}

// Hàm in danh sách giáo viên
void inDanhSachGiaoVien() {
    vector<GiaoVien> dsgv = docGiaoVienTuFile("GiaoVien.txt");
	if (dsgv.empty()) {
		cout << "Khong co du lieu giao vien!\n";
		return;
	}
	// Sắp xếp danh sách giáo viên hợp lệ (tt = true)
	sort(dsgv.begin(), dsgv.end(), [](const GiaoVien& a, const GiaoVien& b) {
		return a.tenGV < b.tenGV;  // Sắp xếp theo tên giáo viên
		});
	// Hiển thị danh sách giáo viên hợp lệ đã sắp xếp
	cout << "\n=================================================== DANH SACH GIAO VIEN =========================================================\n" << endl;
	cout << "| " << left << setw(10) << "Ma GV" << setw(20) << "Ten GV" << setw(15) << "Mon day" << setw(15) << "SDT" << "|" << endl;
	cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
	bool found = false;
	for (const auto& gv : dsgv) {
		if (gv.tt) {  // Kiểm tra giáo viên hợp lệ (tt = true)
			cout << "| " << left << setw(10) << gv.maGV << setw(20) << gv.tenGV << setw(15) << gv.monDay << setw(15) << gv.sdt << "|" << endl;
			found = true;
		}
	}
	cout << "================================================================================================================================\n";
	if (!found) {
		cout << "Khong co giao vien hop le de hien thi!" << endl;
	}
}

// Hàm thêm bảng điểm vào danh sách
void themBangDiem() {
    vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
    vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
	BangDiem bd;    // Tạo đối tượng bảng điểm
    string l, m;
	cout << "Nhap lop can them diem: "; cin >> l;
	cout << "Nhap ma mon hoc: "; cin >> m;
    
    // Lọc học sinh theo lớp
    vector<HocSinh> dshsLop;
    for (const auto& hs : dshs) {
        if (hs.lop == l && hs.tt) { 
            dshsLop.push_back(hs);
        }
    }

    if (dshsLop.empty()) {// Kiểm tra nếu không có học sinh trong lớp đã chọn
        cout << "Khong co hoc sinh trong lop " << l << " de them diem!\n";
        return;
    }

    for (auto& hs : dshsLop) { // Thêm điểm cho từng học sinh trong lớp
        bd.maHS_D = hs.maHS;  // Gán mã học sinh
        bd.maMH = m;  // Mã môn học
        cout << "\nNhap diem cho hoc sinh " << hs.tenHS << " (Mã HS: " << hs.maHS << "):\n";
        bd.nhapDiem();  // Nhập điểm cho học sinh
        dsbd.push_back(bd); // Thêm bảng điểm vào danh sách
    }
    if (confirmAction()) {
        ghiFileBD("BangDiem.txt", dsbd);  // Ghi lại vào file
        cout << "Da them bang diem moi!" << endl;
    }
    else {
        cout << "Huy luu du lieu.\n";
        dsbd.clear(); // Xóa dữ liệu nếu không lưu
    }
}

// Hàm sửa thông tin bảng điểm
void suaBangDiem() {
	vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");
	string maHS, maMon;
	cout << "Nhap ma hoc sinh can sua diem: "; cin >> maHS;
    cout << "Nhap ma mon hoc can sua diem: "; cin >> maMon;

	// Tìm kiếm bảng điểm trong danh sách
	for (auto& bd : dsbd) {
		if (bd.maHS == maHS && bd.maMH == maMon && bd.tt) {
			cout << "\nThong tin bang diem hien tai: " << endl;
			bd.xuatDiem();  // Hiển thị thông tin bảng điểm
			
			int choice;
			cout << "\nBan muon sua thong tin nao?" << endl;
			cout << "1. Sua diem mieng" << endl;
			cout << "2. Sua diem 15 phut" << endl;
			cout << "3. Sua diem kiem tra" << endl;
			cout << "4. Sua diem thi" << endl;
			cout << "Chon chuc nang can sua: ";
			cin >> choice;
			switch (choice) {
			case 1:
				cout << "Nhap diem mieng moi: "; cin >> bd.DM;  // Chỉ sửa điểm miệng
				break;
			case 2:
				cout << "Nhap diem 15 phut moi: "; cin >> bd.DCC;  // Chỉ sửa điểm 15 phút
				break;
			case 3:
				cout << "Nhap diem kiem tra moi: "; cin >> bd.DKT;  // Chỉ sửa điểm kiểm tra
				break;
			case 4:
				cout << "Nhap diem thi moi: "; cin >> bd.DT;  // Chỉ sửa điểm thi
				break;
			default:
				cout << "Chuc nang khong hop le!" << endl;
				return;
			}
			ghiFileBD("BangDiem.txt", dsbd);  // Ghi lại vào file sau khi sửa
			cout << "Da sua thong tin bang diem!" << endl;
			return;
		}
	}
	cout << "Bang diem khong ton tai hoac da bi xoa!" << endl;
}

// Hàm xóa bảng điểm
void xoaBangDiem(vector<BangDiem>& dsbd) {
	string maHS;
	cout << "Nhap ma hoc sinh can xoa diem: ";
	cin >> maHS;
	// Tìm bảng điểm trong danh sách
	for (auto& bd : dsbd) {
		if (bd.maHS == maHS && bd.tt) {  // Kiểm tra bảng điểm còn hợp lệ (tt = true)
			cout << "\nThong tin bang diem can xoa: " << endl;
			bd.xuatDiem();
			char confirm;
			cout << "\nBan co chac chan muon xoa bang diem nay? (y/n): ";
			cin >> confirm;
			if (confirm == 'y' || confirm == 'Y') {
				bd.xoaDiem();  // Đánh dấu bảng điểm này là không hợp lệ (tt = false)
				ghiFileBD("BangDiem.txt", dsbd);  // Ghi lại danh sách bảng điểm sau khi xóa vào file
				cout << "Da xoa bang diem!" << endl;
			}
			else {
				cout << "Huy xoa bang diem." << endl;
			}
			return;
		}
	}
	cout << "Bang diem khong ton tai!" << endl;
}

// Hàm in danh sách bảng điểm theo học sinh
void inBangDiemHocSinh(const string& maHS, const vector<HocSinh>& dshs, const vector<BangDiem>& dsbd) {
    HocSinh hs;
    bool found = false;
    // Tìm học sinh trong danh sách
    for (const auto& h : dshs) {
        if (h.maHS == maHS && h.tt) {  // Kiểm tra học sinh hợp lệ
            hs = h;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay hoc sinh voi ma " << maHS << " hoac hoc sinh khong hop le!\n";
        return;
    }

    // Hiển thị thông tin học sinh và bảng điểm
    cout << endl;
    cout << setfill(' ') << setw(50) << "BANG DIEM CUA HOC SINH " << hs.tenHS << setfill(' ') << endl;
    cout << "Ma Hoc Sinh: " << hs.maHS << endl;
    cout << "Ten Hoc Sinh: " << hs.tenHS << endl;
    cout << "Lop: " << hs.lop << endl;
    cout << "\n===================================================================================\n";
    cout << "| " << left << setw(10) << "Mon Hoc" << setw(15) << "Diem mieng" << setw(15) << "Diem TX" << setw(15) << "Diem KT" << setw(15) << "Diem Thi" << setw(10) << "Diem TB" << "| ";
    cout << "\n-----------------------------------------------------------------------------------\n";

    // In bảng điểm học sinh
    for (const auto& bd : dsbd) {
        if (bd.maHS == maHS && bd.tt) {  // Chỉ in bảng điểm hợp lệ
            cout << "| " << left << setw(10) << bd.maMH << setw(15) << bd.DM << setw(15) << bd.DCC
                << setw(15) << bd.DKT << setw(15) << bd.DT << setw(10) << bd.diemTB() << "| " << endl;
        }
    }
    cout << "===================================================================================\n";
}

// Hàm lưu bảng điểm vào file
void luuBangDiemVaoFile(const string& maHS, const vector<HocSinh>& dshs, const vector<BangDiem>& dsbd) {
    HocSinh hs;
    bool found = false;
    // Tìm học sinh trong danh sách
    for (const auto& h : dshs) {
        if (h.maHS == maHS && h.tt) {  // Kiểm tra học sinh hợp lệ
            hs = h;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay hoc sinh voi ma " << maHS << " hoac hoc sinh khong hop le!\n";
        return;
    }

    // Lưu thông tin học sinh và bảng điểm vào file
    ofstream fileout("BangDiem_" + maHS + ".txt");
    fileout << endl;
    fileout << setfill(' ') << setw(50) << "BANG DIEM CUA HOC SINH " << hs.tenHS << setfill(' ') << endl;
    fileout << "Ma Hoc Sinh: " << hs.maHS << endl;
    fileout << "Ten Hoc Sinh: " << hs.tenHS << endl;
    fileout << "Lop: " << hs.lop << endl;
    fileout << "\n===================================================================================\n";
    fileout << "| " << left << setw(10) << "Mon Hoc" << setw(15) << "Diem mieng" << setw(15) << "Diem TX"
        << setw(15) << "Diem KT" << setw(15) << "Diem Thi" << setw(10) << "Diem TB" << "|" << endl;
    fileout << "-----------------------------------------------------------------------------------\n";

    // Ghi bảng điểm vào file
    for (const auto& bd : dsbd) {
        if (bd.maHS == maHS && bd.tt) {  // Chỉ ghi bảng điểm hợp lệ
            fileout << "| " << left << setw(10) << bd.maMH << setw(15) << bd.DM << setw(15) << bd.DCC
                << setw(15) << bd.DKT << setw(15) << bd.DT << setw(10) << bd.diemTB() << "| " << endl;
        }
    }

    fileout << "===================================================================================\n";
    fileout.close();
    cout << "Bang diem da duoc luu vao file BangDiem_" << maHS << ".txt\n";
}

// Hàm lưu danh sách điểm theo môn học vào file
void luuDanhSachDiemTheoMonVaoFile(const string& maMH, const vector<HocSinh>& dshs, const vector<BangDiem>& diemTheoMon) {
    // Lưu danh sách điểm theo môn học vào file
    ofstream fileout("DanhSachDiemTheoMon_" + maMH + ".txt");

    fileout << "\n=================== DANH SACH DIEM THEO MON " << maMH << " ====================\n" << endl;
    fileout << "=======================================================================\n";
    fileout << "| " << left << setw(15) << "Ma hoc sinh" << setw(10) << "Ma mon"
        << setw(8) << "Mieng" << setw(8) << "15 phut" << setw(8) << "KT"
        << setw(8) << "Thi" << setw(10) << "Diem TB" << "|\n";
    fileout << "---------------------------------------------------------------------\n";

    // Duyệt qua bảng điểm theo môn học và ghi vào file
    for (const auto& bd : diemTheoMon) {
        for (const auto& hs : dshs) {
            if (hs.maHS == bd.maHS && hs.tt && bd.maMH == maMH) {  // Chỉ ghi học sinh hợp lệ và đúng mã môn học
                fileout << "| " << left << setw(15) << bd.maHS
                    << setw(10) << bd.maMH
                    << setw(8) << bd.DM
                    << setw(8) << bd.DCC
                    << setw(8) << bd.DKT
                    << setw(8) << bd.DT
                    << setw(10) << bd.diemTB() << "|\n";
                break;  // Dừng vòng lặp khi ghi xong học sinh
            }
        }
    }

    fileout << "=======================================================================\n";
    fileout.close();
    cout << "Danh sach da duoc luu vao file DanhSachDiemTheoMon_" << maMH << ".txt\n";
}

// Hàm in danh sách điểm theo môn học và lớp học
void inDanhSachDiemTheoMon(vector<HocSinh>& dshs, vector<BangDiem>& dsbd) {
    if (dshs.empty() || dsbd.empty()) {
        cout << "Khong co du lieu!\n";
        return;
    }

    string maMH;
    cout << "Nhap ma mon hoc: ";
    cin >> maMH;

    // Lọc điểm theo môn học (chỉ lấy bảng điểm hợp lệ)
    vector<BangDiem> diemTheoMon;
    for (const auto& bd : dsbd) {
        if (bd.tt && bd.maMH == maMH) {  // Kiểm tra bảng điểm hợp lệ mà không cần trim
            diemTheoMon.push_back(bd);
        }
    }

    if (diemTheoMon.empty()) {
        cout << "Khong co du lieu diem cho mon hoc " << maMH << "!\n";
        return;
    }

    // Hiển thị danh sách điểm theo môn học
    cout << "\n=================== DANH SACH DIEM THEO MON " << maMH << " ====================\n" << endl;
    cout << "=====================================================================\n";
    cout << "| " << left << setw(15) << "Ma hoc sinh" << setw(10) << "Ma mon"
        << setw(8) << "Mieng" << setw(8) << "15 phut" << setw(8) << "KT"
        << setw(8) << "Thi" << setw(10) << "Diem TB" << "|\n";
    cout << "---------------------------------------------------------------------\n";

    // Duyệt qua bảng điểm theo môn học
    for (const auto& bd : diemTheoMon) {
        // Tìm tên học sinh tương ứng trong danh sách học sinh hợp lệ
        for (const auto& hs : dshs) {
            if (hs.maHS == bd.maHS && hs.tt) {  // Chỉ lấy học sinh hợp lệ
                cout << "| " << left << setw(15) << bd.maHS
                    << setw(10) << bd.maMH
                    << setw(8) << bd.DM
                    << setw(8) << bd.DCC
                    << setw(8) << bd.DKT
                    << setw(8) << bd.DT
                    << setw(10) << bd.diemTB() << "|\n";
                break;  // Dừng vòng lặp khi tìm thấy học sinh
            }
        }
    }
    cout << "=====================================================================\n";

    // Hỏi người dùng có muốn lưu danh sách vào file không
    char save;
    cout << "Ban co muon luu danh sach vao file? (Y/N): ";
    cin >> save;

    if (tolower(save) == 'y') {
        // Gọi hàm lưu danh sách điểm theo môn học vào file
        luuDanhSachDiemTheoMonVaoFile(maMH, dshs, diemTheoMon);
    }
}

//menu
void menu() {
    cout << "\n========================= MENU =========================" << endl;
    cout << "|1. Quan ly hoc sinh                                   |" << endl;
    cout << "|2. Quan ly giao vien                                  |" << endl;
    cout << "|3. Quan ly bang diem                                  |" << endl;
    cout << "|4. Bao cao thong ke                                   |" << endl;
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
            //Quản lý học sinh
        case 1:
        {
            system("cls");
            int chonCN;
            while (true) {
                displaySubMenu("Hoc Sinh");
                cin >> chonCN;
                switch (chonCN)
                {
                case 1: //Thêm học sinh
                {
                    themHocSinh();
                    pauseAndClear();
                    break;
                };

                case 2: //Sửa thông tin học sinh
                {
                    suaHocSinh();
                    pauseAndClear();
                    break;
                };

                case 3: //Xóa học sinh
                {
                    xoaHocSinh();
                    pauseAndClear();
                    break;
                };

                case 4: //Xem danh sách học sinh + tìm kiếm
                {
                    timKiemHS();
                    pauseAndClear();
                    break;
                };

                case 0: //Quay lại
                {
                    pauseAndClear();
                    break;
                };
                default:
                {
                    cout << "Chon chuc nang khong hop le. Vui long chon lai.\n";
                    //pauseAndClear();
                    // << "Chon chuc nang: ";
                    cin.ignore();
                    cin.get();
                    break;
                }
                }
            }
            pauseAndClear();
            break;
        };

        //Quản lý giáo viên
        case 2:
        {
            system("cls");
            int chonCN;
            while (true) {
                displaySubMenu("Giao Vien");
                cin >> chonCN;
                switch (chonCN)
                {
                case 1: //Thêm giáo viên
                {
                    themGiaoVien();
                    pauseAndClear();
                    break;
                };

                case 2: //Sửa thông tin giáo viên
                {
                    suaGiaoVien();
                    pauseAndClear();
                    break;
                };

                case 3: //Xóa giáo viên
                {
                    xoaGiaoVien();
                    pauseAndClear();
                    break;
                };

                case 4: //Xem danh sách giáo viên
                {
                    inDanhSachGiaoVien();
                    pauseAndClear();
                    break;
                };

                case 0: //Quay lại
                {
                    pauseAndClear();
                    break;
                };

                default:
                {
                    cout << "Chon chuc nang khong hop le. Vui long chon lai.\n";
                    pauseAndClear();
                    //cout << "Chon chuc nang: ";
                    break;
                }
                }
            }

        };

        //Quản lý điểm
        case 3:
        {
            system("cls");
            int chonCN;
            while (true) {
                displaySubMenu("BangDiem");
                cin >> chonCN;
                switch (chonCN)
                {
                case 1: //Thêm bảng điểm
                {
                    themBangDiem();
                    pauseAndClear();
                    break;
                };

                case 2: //Sửa bảng điểm
                {
                    suaBangDiem();
                    pauseAndClear();
                    break;
                };

                case 3: //Xóa bảng điểm
                {
                    xoaBangDiem(dsbd);
                    pauseAndClear();
                    break;
                };

                case 4: //In bảng điểm
                {

                };

                case 0:// Quay lại
                {
                    pauseAndClear();
                    break;
                };
                }

                pauseAndClear();
                break;
            };
		};
        case 4: //Báo cáo thống kê
        {

        };

            //case 10: // Hiển thị học sinh có điểm trung bình cao nhất
            //       {
            //           vector<HocSinh> dshs = docHocSinhTuFile("HocSinh.txt");
            //           vector<BangDiem> dsbd = docBangDiemTuFile("BangDiem.txt");

            //           if (dshs.empty() || dsbd.empty()) {
            //               cout << "Khong co du lieu de hien thi!\n";
            //               break;
            //           }

            //           float maxDiemTB = 0;
            //           vector<HocSinh> hsMaxDiemTB;

            //           // Tính điểm trung bình cho tất cả các môn của từng học sinh
            //           for (const auto & hs : dshs) {
            //               if (!hs.tt) continue;
            //               float diemTB = tinhDiemTB(hs.maHS, dsbd); // Gọi hàm tính điểm trung bình

            //               // Tìm học sinh có điểm trung bình cao nhất
            //               if (diemTB > maxDiemTB) {
            //                   maxDiemTB = diemTB;
            //                   hsMaxDiemTB.clear();
            //                   hsMaxDiemTB.push_back(hs);
            //               }
            //               else if (diemTB == maxDiemTB) {
            //                   hsMaxDiemTB.push_back(hs);
            //               }
            //           }

            //           // Hiển thị danh sách học sinh có điểm trung bình cao nhất
            //           cout << "\nHoc sinh co diem trung binh cao nhat:\n";
            //           cout << "| " << left << setw(10) << "Ma HS" << setw(20) << "Ten HS" << setw(10) << "Lop" << setw(8) << "TB" << "|\n";

            //           for (const auto& hs : hsMaxDiemTB) {
            //               cout << "| " << left << setw(10) << hs.maHS << setw(20) << hs.tenHS << setw(10) << hs.lop;
            //               cout << setw(8) << maxDiemTB << "|\n";
            //           }

            //           pauseAndClear();
            //           break;
            //       };

        case 0: {
            cout << "Ban co thuc su muon thoat chuong trinh khong? (Y/N): ";
            char a;
            cin >> a;
            break;
        }

        default: {
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
            pauseAndClear();
            // cout << "Chon chuc nang: ";
            cin.ignore();
            cin.get();
        }
        }





    } while (chon != 0);

    return 0;
}