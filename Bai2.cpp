#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Person {
protected:
    string hoVaTen;
    string ngaySinh;
    string queQuan;

public:
    Person() {}

    Person(string hoVaTen, string ngaySinh, string queQuan) {
        this->hoVaTen = hoVaTen;
        this->ngaySinh = ngaySinh;
        this->queQuan = queQuan;
    }

    virtual void nhap() {
        cout << "Nhap ho va ten: ";
        getline(cin >> ws, hoVaTen);
        cout << "Nhap ngay sinh (nn/mm/yyyy): ";
        getline(cin, ngaySinh);
        cout << "Nhap que quan: ";
        getline(cin, queQuan);
    }

    virtual void xuat() {
        cout << left << setw(22) << hoVaTen
             << left << setw(15) << ngaySinh
             << left << setw(20) << queQuan;
    }

    virtual ~Person() {}
};

class KySu : public Person {
private:
    string nganhHoc;
    int namTotNghiep;

public:
    KySu() : Person(), namTotNghiep(0) {}

    void nhap() override {
        Person::nhap();
        cout << "Nhap nganh hoc: ";
        getline(cin >> ws, nganhHoc);
        cout << "Nhap nam tot nghiep (<= 2026): ";
        cin >> namTotNghiep;
        while (namTotNghiep > 2026 || namTotNghiep < 1900) {
            cout << "Nam tot nghiep khong hop le. Nhap lai nam tot nghiep : ";
            cin >> namTotNghiep;
        }
    }

    void xuat() override {
        Person::xuat();
        cout << left << setw(20) << nganhHoc
             << right << setw(12) << namTotNghiep << endl;
    }

    static void inTieuDe() {
        cout << string(89, '-') << endl;
        cout << left << setw(22) << "Ho Ten"
             << left << setw(15) << "Ngay Sinh"
             << left << setw(20) << "Que Quan"
             << left << setw(20) << "Nganh Hoc"
             << right << setw(12) << "Nam TN" << endl;
        cout << string(89, '-') << endl;
    }

    static void inKeBang() {
        cout << string(89, '-') << endl;
    }

    int getNamTotNghiep() const {
        return namTotNghiep;
    }
};

int main() {
    int n;
    cout << "Nhap so luong ky su: ";
    cin >> n;

    vector<KySu> danhSachKySu(n);
    for (int i = 0; i < n; i++) {
        cout << "\nNhap thong tin ky su thu " << (i + 1) << ":" << endl;
        danhSachKySu[i].nhap();
    }

    cout << "\n--- DANH SACH CAC KY SU ---" << endl;
    KySu::inTieuDe();
    for (size_t i = 0; i < danhSachKySu.size(); i++) {
        danhSachKySu[i].xuat();
    }
    KySu::inKeBang();

    if (!danhSachKySu.empty()) {
        int maxNamTotNghiep = danhSachKySu[0].getNamTotNghiep();
        for (size_t i = 1; i < danhSachKySu.size(); i++) {
            if (danhSachKySu[i].getNamTotNghiep() > maxNamTotNghiep) {
                maxNamTotNghiep = danhSachKySu[i].getNamTotNghiep();
            }
        }

        cout << "\n--- THONG TIN CAC KY SU TOT NGHIEP GAN DAY NHAT (Nam " << maxNamTotNghiep << ") ---" << endl;
        KySu::inTieuDe();
        for (size_t i = 0; i < danhSachKySu.size(); i++) {
            if (danhSachKySu[i].getNamTotNghiep() == maxNamTotNghiep) {
                danhSachKySu[i].xuat();
            }
        }
        KySu::inKeBang();
    }

    return 0;
}
