#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Nguoi {
protected:
    string hoTen;
    string ngaySinh;

public:
    Nguoi() {}

    Nguoi(string hoTen, string ngaySinh) {
        this->hoTen = hoTen;
        this->ngaySinh = ngaySinh;
    }

    virtual void nhap() {
        cout << "Nhap ho ten: ";
        getline(cin >> ws, hoTen);
        cout << "Nhap ngay sinh (nn/mm/yyyy): ";
        getline(cin, ngaySinh);
    }

    virtual void hienThi() {
        cout << left << setw(22) << hoTen 
             << left << setw(15) << ngaySinh;
    }

    virtual ~Nguoi() {}
};

class ThiSinh : public Nguoi {
private:
    string soBaoDanh;
    double diemToan;
    double diemLy;
    double diemHoa;

public:
    ThiSinh() : Nguoi(), diemToan(0), diemLy(0), diemHoa(0) {}

    string getSoBaoDanh() const {
        return soBaoDanh;
    }

    void nhapSBD(const vector<ThiSinh>& ds) {
        bool trung;
        do {
            trung = false;
            cout << "Nhap so bao danh: ";
            getline(cin >> ws, soBaoDanh);
            for (size_t i = 0; i < ds.size(); i++) {
                if (ds[i].getSoBaoDanh() == soBaoDanh) {
                    cout << "So bao danh bi trung. Nhap lai!" << endl;
                    trung = true;
                    break;
                }
            }
        } while (trung);
    }

    void nhap(const vector<ThiSinh>& ds) {
        nhapSBD(ds);
        Nguoi::nhap();
        
        cout << "Nhap diem toan : ";
        cin >> diemToan;
        while (diemToan < 0 || diemToan > 10) {
            cout << "Diem khong hop le. Nhap lai diem toan : ";
            cin >> diemToan;
        }

        cout << "Nhap diem ly : ";
        cin >> diemLy;
        while (diemLy < 0 || diemLy > 10) {
            cout << "Diem khong hop le. Nhap lai diem ly (0-10): ";
            cin >> diemLy;
        }

        cout << "Nhap diem hoa : ";
        cin >> diemHoa;
        while (diemHoa < 0 || diemHoa > 10) {
            cout << "Diem khong hop le. Nhap lai diem hoa (0-10): ";
            cin >> diemHoa;
        }
    }

    void hienThi() override {
        cout << left << setw(10) << soBaoDanh;
        Nguoi::hienThi();
        cout << right << setw(8) << diemToan
             << right << setw(8) << diemLy
             << right << setw(8) << diemHoa
             << right << setw(12) << tinhTongDiem()
             << right << setw(12) << tinhDiemTrungBinh() << endl;
    }

    static void inTieuDe() {
        cout << string(95, '-') << endl;
        cout << left << setw(10) << "SBD"
             << left << setw(22) << "Ho Ten"
             << left << setw(15) << "Ngay Sinh"
             << right << setw(8) << "Toan"
             << right << setw(8) << "Ly"
             << right << setw(8) << "Hoa"
             << right << setw(12) << "Tong Diem"
             << right << setw(12) << "Diem TB" << endl;
        cout << string(95, '-') << endl;
    }

    static void inKeBang() {
        cout << string(95, '-') << endl;
    }

    double tinhTongDiem() const {
        return diemToan + diemLy + diemHoa;
    }

    double tinhDiemTrungBinh() const {
        return tinhTongDiem() / 3.0;
    }

    double getDiemTrungBinh() const {
        return tinhDiemTrungBinh();
    }
};

bool soSanhDiem(const ThiSinh& a, const ThiSinh& b) {
    return a.getDiemTrungBinh() > b.getDiemTrungBinh();
}

int main() {
    int n;
    cout << "Nhap so luong thi sinh (it nhat 3): ";
    cin >> n;
    while (n < 3) {
        cout << "Phai nhap it nhat 3 thi sinh. Nhap lai: ";
        cin >> n;
    }

    vector<ThiSinh> danhSachThiSinh;
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin thi sinh thu " << (i + 1) << ":" << endl;
        ThiSinh ts;
        ts.nhap(danhSachThiSinh);
        danhSachThiSinh.push_back(ts);
    }

    cout << "\n--- DANH SACH THI SINH VUA NHAP ---" << endl;
    ThiSinh::inTieuDe();
    for (size_t i = 0; i < danhSachThiSinh.size(); i++) {
        danhSachThiSinh[i].hienThi();
    }
    ThiSinh::inKeBang();

    sort(danhSachThiSinh.begin(), danhSachThiSinh.end(), soSanhDiem);

    cout << "\n--- DANH SACH THI SINH SAP XEP THEO DIEM TB GIAM DAN ---" << endl;
    ThiSinh::inTieuDe();
    for (size_t i = 0; i < danhSachThiSinh.size(); i++) {
        danhSachThiSinh[i].hienThi();
    }
    ThiSinh::inKeBang();

    int demDat = 0;
    for (size_t i = 0; i < danhSachThiSinh.size(); i++) {
        if (danhSachThiSinh[i].tinhTongDiem() >= 20) {
            demDat++;
        }
    }
    cout << "\nSo luong thi sinh dat (tong diem >= 20): " << demDat << endl;

    return 0;
}
