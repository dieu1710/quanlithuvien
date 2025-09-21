#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <limits> // Để sử dụng numeric_limits

// Sử dụng namespace std để tiện lợi
using namespace std;

// --- Định nghĩa mã màu ANSI ---
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

// Class Ngày tháng để quản lý ngày mượn/trả
class Date {
private:
    int day, month, year;
public:
    Date(int d = 0, int m = 0, int y = 0) : day(d), month(m), year(y) {}

    void nhap() {
        cout << CYAN << "Nhap ngay: " << RESET; cin >> day;
        cout << CYAN << "Nhap thang: " << RESET; cin >> month;
        cout << CYAN << "Nhap nam: " << RESET; cin >> year;
    }

    void xuat() const {
        cout << day << "/" << month << "/" << year;
    }

    Date operator+(int days) const {
        tm timeinfo = {0};
        timeinfo.tm_mday = day;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_hour = 0;
        timeinfo.tm_min = 0;
        timeinfo.tm_sec = 0;
        mktime(&timeinfo);

        timeinfo.tm_mday += days;
        mktime(&timeinfo);

        return Date(timeinfo.tm_mday, timeinfo.tm_mon + 1, timeinfo.tm_year + 1900);
    }

    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    static Date getCurrentDate() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return Date(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    }
};

// Class Sách
class Sach {
private:
    string maSach, tenSach, tacGia, theLoai;
    int soLuong;
    bool tinhTrang;
public:
    Sach(string ms = "", string ts = "", string tg = "", string tl = "", int sl = 0)
        : maSach(ms), tenSach(ts), tacGia(tg), theLoai(tl), soLuong(sl) {
        tinhTrang = (soLuong > 0);
    }

    void nhap() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Nhap ma sach: " << RESET; getline(cin, maSach);
        cout << CYAN << "Nhap ten sach: " << RESET; getline(cin, tenSach);
        cout << CYAN << "Nhap tac gia: " << RESET; getline(cin, tacGia);
        cout << CYAN << "Nhap the loai: " << RESET; getline(cin, theLoai);
        cout << CYAN << "Nhap so luong: " << RESET; cin >> soLuong;
        tinhTrang = (soLuong > 0);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void xuat() const {
        cout << "Ma sach: " << BOLDWHITE << maSach << RESET << ", Ten: " << BOLDWHITE << tenSach
             << RESET << ", Tac gia: " << tacGia << ", The loai: " << theLoai
             << ", So luong: " << soLuong << ", Tinh trang: "
             << (tinhTrang ? BOLDGREEN "Co san" : BOLDRED "Da het") << RESET << endl;
    }

    string getMaSach() const { return maSach; }
    string getTenSach() const { return tenSach; }
    string getTacGia() const { return tacGia; }
    string getTheLoai() const { return theLoai; }
    int getSoLuong() const { return soLuong; }
    bool getTinhTrang() const { return tinhTrang; }

    void setSoLuong(int sl) {
        soLuong = sl;
        tinhTrang = (soLuong > 0);
    }

    void capNhatThongTin() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << BOLDYELLOW << "Cap nhat thong tin sach " << tenSach << ":\n" << RESET;
        cout << CYAN << "Nhap ten moi (Enter de bo qua): " << RESET;
        string ten; getline(cin, ten);
        if (!ten.empty()) tenSach = ten;

        cout << CYAN << "Nhap tac gia moi (Enter de bo qua): " << RESET;
        string tg; getline(cin, tg);
        if (!tg.empty()) tacGia = tg;

        cout << CYAN << "Nhap the loai moi (Enter de bo qua): " << RESET;
        string tl; getline(cin, tl);
        if (!tl.empty()) theLoai = tl;

        cout << CYAN << "Nhap so luong moi (Nhap 0 de bo qua): " << RESET;
        int sl_input;
        cin >> sl_input;
        if (sl_input > 0) {
            soLuong = sl_input;
            tinhTrang = (soLuong > 0);
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
};

// Class Bạn đọc
class BanDoc {
private:
    string maSV, hoTen;
public:
    BanDoc(string ms = "", string ht = "") : maSV(ms), hoTen(ht) {}

    void nhap() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Nhap ma sinh vien: " << RESET; getline(cin, maSV);
        cout << CYAN << "Nhap ho ten: " << RESET; getline(cin, hoTen);
    }

    void xuat() const {
        cout << "Ma SV: " << BOLDWHITE << maSV << RESET << ", Ho ten: " << BOLDWHITE << hoTen << RESET << endl;
    }

    string getMaSV() const { return maSV; }
    string getHoTen() const { return hoTen; }
};

// Class Phiếu mượn
class PhieuMuon {
private:
    string maPhieu;
    Sach* sach;
    BanDoc* banDoc;
    Date ngayMuon, hanTra;
    bool daTra;
public:
    PhieuMuon(Sach* s = nullptr, BanDoc* bd = nullptr, int soNgayMuon = 7)
        : sach(s), banDoc(bd), daTra(false) {
        ngayMuon = Date::getCurrentDate();
        hanTra = ngayMuon + soNgayMuon;
        srand(time(NULL));
        maPhieu = "PM" + to_string(rand() % 900000 + 100000);
    }

    bool isQuaHan() const {
        if (daTra) return false;
        Date today = Date::getCurrentDate();
        return hanTra < today;
    }

    void xuat() const {
        cout << "Ma phieu: " << BOLDYELLOW << maPhieu << RESET << endl;
        cout << "Sach: ";
        if (sach) sach->xuat();
        else cout << RED << "Khong tim thay sach!" << RESET << endl;

        cout << "Ban doc: ";
        if (banDoc) banDoc->xuat();
        else cout << RED << "Khong tim thay ban doc!" << RESET << endl;

        cout << "Ngay muon: "; ngayMuon.xuat(); cout << endl;
        cout << "Han tra: "; hanTra.xuat(); cout << endl;
        cout << "Tinh trang: " << (daTra ? BOLDGREEN "Da tra" : YELLOW "Dang muon") << RESET;
        if (isQuaHan()) cout << BOLDRED " (QUA HAN)" << RESET;
        cout << endl;
    }

    string getMaPhieu() const { return maPhieu; }
    Sach* getSach() const { return sach; }
    BanDoc* getBanDoc() const { return banDoc; }
    bool getDaTra() const { return daTra; }
    void setDaTra(bool dt) { daTra = dt; }
};

// Class Quản lý thư viện
class QuanLyThuVien {
private:
    vector<Sach> danhSachSach;
    vector<BanDoc> danhSachBanDoc;
    vector<PhieuMuon*> danhSachPhieuMuon;

public:
    ~QuanLyThuVien() {
        for (auto pm : danhSachPhieuMuon) {
            delete pm;
        }
        danhSachPhieuMuon.clear();
    }

    void themSach() {
        cout << BOLDMAGENTA << "\n--- THEM SACH MOI ---\n" << RESET;
        Sach s;
        s.nhap();
        danhSachSach.push_back(s);
        cout << BOLDGREEN << "Them sach thanh cong!\n" << RESET;
    }

    void themBanDoc() {
        cout << BOLDMAGENTA << "\n--- THEM BAN DOC MOI ---\n" << RESET;
        BanDoc bd;
        bd.nhap();
        danhSachBanDoc.push_back(bd);
        cout << BOLDGREEN << "Them ban doc thanh cong!\n" << RESET;
    }

    void hienThiSach() const {
        cout << BOLDYELLOW << "\n--- DANH SACH SACH ---\n" << RESET;
        if (danhSachSach.empty()) {
            cout << YELLOW << "Chua co sach nao trong thu vien.\n" << RESET;
            return;
        }
        for (const auto& s : danhSachSach) {
            s.xuat();
        }
        cout << BOLDYELLOW << "-----------------------\n" << RESET;
    }

    void hienThiBanDoc() const {
        cout << BOLDYELLOW << "\n--- DANH SACH BAN DOC ---\n" << RESET;
        if (danhSachBanDoc.empty()) {
            cout << YELLOW << "Chua co ban doc nao.\n" << RESET;
            return;
        }
        for (const auto& bd : danhSachBanDoc) {
            bd.xuat();
        }
        cout << BOLDYELLOW << "-------------------------\n" << RESET;
    }

    Sach* timSachTheoMa(const string& ma) {
        for (auto& s : danhSachSach) {
            if (s.getMaSach() == ma) return &s;
        }
        return nullptr;
    }

    BanDoc* timBanDocTheoMa(const string& ma) {
        for (auto& bd : danhSachBanDoc) {
            if (bd.getMaSV() == ma) return &bd;
        }
        return nullptr;
    }

    void muonSach() {
        cout << BOLDMAGENTA << "\n--- MUON SACH ---\n" << RESET;
        string maSach, maSV;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Nhap ma sach: " << RESET; getline(cin, maSach);
        cout << CYAN << "Nhap ma sinh vien: " << RESET; getline(cin, maSV);

        Sach* s = timSachTheoMa(maSach);
        BanDoc* bd = timBanDocTheoMa(maSV);

        if (!s) {
            cout << BOLDRED << "Khong tim thay sach voi ma " << maSach << "!\n" << RESET;
            return;
        }
        if (!bd) {
            cout << BOLDRED << "Khong tim thay ban doc voi ma " << maSV << "!\n" << RESET;
            return;
        }

        if (s->getSoLuong() <= 0) {
            cout << YELLOW << "Sach \"" << s->getTenSach() << "\" da het! Khong the muon.\n" << RESET;
            return;
        }

        int soNgayMuon;
        cout << CYAN << "Nhap so ngay muon: " << RESET; cin >> soNgayMuon;
        if (soNgayMuon <= 0) {
            cout << RED << "So ngay muon phai lon hon 0.\n" << RESET;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        PhieuMuon* pm = new PhieuMuon(s, bd, soNgayMuon);
        danhSachPhieuMuon.push_back(pm);
        s->setSoLuong(s->getSoLuong() - 1);

        cout << BOLDGREEN << "Muon sach thanh cong. Ma phieu: " << pm->getMaPhieu() << "\n" << RESET;
    }

    void traSach() {
        cout << BOLDMAGENTA << "\n--- TRA SACH ---\n" << RESET;
        string maPhieu;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Nhap ma phieu: " << RESET; getline(cin, maPhieu);

        bool found = false;
        for (auto pm : danhSachPhieuMuon) {
            if (pm->getMaPhieu() == maPhieu) {
                found = true;
                if (!pm->getDaTra()) {
                    pm->setDaTra(true);
                    pm->getSach()->setSoLuong(pm->getSach()->getSoLuong() + 1);

                    if (pm->isQuaHan()) {
                        cout << BOLDRED << "Sach tra qua han! Phat 50.000 VND\n" << RESET;
                    } else {
                        cout << BOLDGREEN << "Sach tra dung han.\n" << RESET;
                    }
                    cout << BOLDGREEN << "Tra sach thanh cong!\n" << RESET;
                } else {
                    cout << YELLOW << "Phieu muon nay da duoc tra truoc do.\n" << RESET;
                }
                return;
            }
        }
        if (!found) {
            cout << BOLDRED << "Khong tim thay phieu muon voi ma " << maPhieu << "!\n" << RESET;
        }
    }

    // Hàm timSach() được sửa đổi để tìm kiếm theo nhiều tiêu chí
    void timSach() const {
        cout << BOLDMAGENTA << "\n--- TIM KIEM SACH THEO NHIEU TIEU CHI ---\n" << RESET;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Đảm bảo buffer sạch trước khi đọc các string

        string keywordTenSach, keywordTacGia, keywordTheLoai, keywordMaSach;

        cout << CYAN << "Nhap ten sach (enter de bo qua): " << RESET;
        getline(cin, keywordTenSach);
        cout << CYAN << "Nhap tac gia (enter de bo qua): " << RESET;
        getline(cin, keywordTacGia);
        cout << CYAN << "Nhap the loai (enter de bo qua): " << RESET;
        getline(cin, keywordTheLoai);
        cout << CYAN << "Nhap ma sach (enter de bo qua): " << RESET;
        getline(cin, keywordMaSach);

        cout << BOLDYELLOW << "\n--- KET QUA TIM KIEM ---\n" << RESET;
        bool found = false;
        for (const auto& s : danhSachSach) {
            bool matchTenSach = keywordTenSach.empty() || (s.getTenSach().find(keywordTenSach) != string::npos);
            bool matchTacGia = keywordTacGia.empty() || (s.getTacGia().find(keywordTacGia) != string::npos);
            bool matchTheLoai = keywordTheLoai.empty() || (s.getTheLoai().find(keywordTheLoai) != string::npos);
            bool matchMaSach = keywordMaSach.empty() || (s.getMaSach() == keywordMaSach);

            // Sách khớp khi TẤT CẢ các tiêu chí không rỗng đều khớp
            if (matchTenSach && matchTacGia && matchTheLoai && matchMaSach) {
                s.xuat();
                found = true;
            }
        }
        if (!found) {
            cout << YELLOW << "Khong tim thay sach nao phu hop voi cac tieu chi da cho.\n" << RESET;
        }
        cout << BOLDYELLOW << "------------------------\n" << RESET;
    }

    void sachQuaHan() const {
        cout << BOLDRED << "\n--- DANH SACH SACH QUA HAN ---\n" << RESET;
        bool hasOverdue = false;
        for (const auto pm : danhSachPhieuMuon) {
            if (pm->isQuaHan()) {
                pm->xuat();
                cout << BOLDRED << "--------------------\n" << RESET;
                hasOverdue = true;
            }
        }
        if (!hasOverdue) {
            cout << GREEN << "Khong co sach nao dang qua han.\n" << RESET;
        }
        cout << BOLDRED << "-------------------------------\n" << RESET;
    }

    void capNhatSach() {
        cout << BOLDMAGENTA << "\n--- CAP NHAT THONG TIN SACH ---\n" << RESET;
        string maSach;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << CYAN << "Nhap ma sach can cap nhat: " << RESET; getline(cin, maSach);

        Sach* s = timSachTheoMa(maSach);
        if (s) {
            s->capNhatThongTin();
            cout << BOLDGREEN << "Cap nhat thong tin sach thanh cong!\n" << RESET;
        } else {
            cout << BOLDRED << "Khong tim thay sach voi ma " << maSach << "!\n" << RESET;
        }
    }
};

// Hàm main
int main() {
    srand(static_cast<unsigned int>(time(0)));

    QuanLyThuVien qltv;
    int choice;

    do {
        cout << BOLDBLUE << "\n=== CHUONG TRINH QUAN LY THU VIEN ===\n" << RESET;
        cout << WHITE << "1. Them sach moi\n";
        cout << WHITE << "2. Them ban doc moi\n";
        cout << WHITE << "3. Hien thi tat ca sach\n";
        cout << WHITE << "4. Hien thi tat ca ban doc\n";
        cout << WHITE << "5. Muon sach\n";
        cout << WHITE << "6. Tra sach\n";
        cout << WHITE << "7. Tim kiem sach\n";
        cout << WHITE << "8. Hien thi sach dang muon bi qua han\n";
        cout << WHITE << "9. Cap nhat thong tin sach\n";
        cout << BOLDRED << "0. Thoat chuong trinh\n" << RESET;
        cout << BOLDGREEN << "Lua chon cua ban: " << RESET;
        cin >> choice;

        if (cin.fail()) {
            cout << BOLDRED << "Nhap sai dinh dang! Vui long nhap mot so.\n" << RESET;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: qltv.themSach(); break;
            case 2: qltv.themBanDoc(); break;
            case 3: qltv.hienThiSach(); break;
            case 4: qltv.hienThiBanDoc(); break;
            case 5: qltv.muonSach(); break;
            case 6: qltv.traSach(); break;
            case 7: qltv.timSach(); break;
            case 8: qltv.sachQuaHan(); break;
            case 9: qltv.capNhatSach(); break;
            case 0: cout << BOLDCYAN << "Dang thoat chuong trinh. Tam biet!\n" << RESET; break;
            default: cout << BOLDRED << "Lua chon khong hop le. Vui long chon lai!\n" << RESET;
        }
    } while (choice != 0);

    return 0;
}
