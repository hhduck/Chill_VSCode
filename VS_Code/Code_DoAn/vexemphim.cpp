#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class KhachHang {
protected:
    string hoTen;
    string soDT;
    int soVe;
    double giaVe;

public:
    KhachHang(string _hoTen = "", string _soDT = "", int _soVe = 1, double _giaVe = 1.0)
        : hoTen(_hoTen), soDT(_soDT), soVe(_soVe), giaVe(_giaVe) {
    }

    virtual ~KhachHang() {}

    virtual string getLoaiVe() const = 0;
    virtual int getHoaDon() const = 0;
    virtual string getQuyenDoiTra() const = 0;

    virtual void nhapThongTin() {
        cin.ignore();
        cout << "Ho ten: ";
        getline(cin, hoTen);
        cout << "So dien thoai: ";
        getline(cin, soDT);
        cout << "So ve: ";
        cin >> soVe;
    }

    virtual void print() const {
        cout << left << setw(15) << getLoaiVe()
            << left << setw(15) << hoTen
            << left << setw(15) << soDT
            << left << setw(15) << soVe
            << left << setw(15) << getHoaDon()
            << left << setw(10) << getQuyenDoiTra();
    }
    friend istream& operator>>(istream& is, KhachHang& kh) {
        kh.nhapThongTin();
        return is;
    }

    friend ostream& operator<<(ostream& os, const KhachHang& kh) {
        kh.print();
        return os;
    }


};

class VeThuong : public KhachHang {
public:
    VeThuong(string _hoTen = "", string _soDT = "", int _soVe = 1, double _giaVe = 1.0)
        : KhachHang(_hoTen, _soDT, _soVe, _giaVe) {}

    string getLoaiVe() const override {
        return "Thuong";
    }

    int getHoaDon() const override {
        double hoaDonDouble;
        if (soVe < 5)
            hoaDonDouble = soVe * giaVe;
        else
            hoaDonDouble = soVe * giaVe * 0.9;
        return (int)hoaDonDouble;
    }

    string getQuyenDoiTra() const override {
        return "Co";
    }
};

class VeKM : public KhachHang {
    double heSoKM;

public:
    VeKM(string _hoTen = "", string _soDT = "", int _soVe = 1, double _giaVe = 1.0, double _heSoKM = 0.0)
        : KhachHang(_hoTen, _soDT, _soVe, _giaVe), heSoKM(_heSoKM) {}

    string getLoaiVe() const override {
        return "Khuyen Mai";
    }

    int getHoaDon() const override {
        double hoaDonDouble = soVe * giaVe - soVe * giaVe * heSoKM;
        return (int)hoaDonDouble;
    }

    string getQuyenDoiTra() const override {
        return "Khong";
    }

    void nhapThongTin() override {
        KhachHang::nhapThongTin();
        cout << "He so khuyen mai (vi du: 0.2 cho 20%): ";
        cin >> heSoKM;
    }
};

class VeVIP : public KhachHang {
    int phiPhucVu;

public:
    VeVIP(string _hoTen = "", string _soDT = "", int _soVe = 1, double _giaVe = 1.0, int _phiPhucVu = 0)
        : KhachHang(_hoTen, _soDT, _soVe, _giaVe), phiPhucVu(_phiPhucVu) {}

    string getLoaiVe() const override {
        return "VIP";
    }

    int getHoaDon() const override {
        double hoaDonDouble;
        if (soVe < 5)
            hoaDonDouble = soVe * giaVe + soVe * phiPhucVu;
        else
            hoaDonDouble = (soVe * giaVe + soVe * phiPhucVu) * 0.8;
        return (int)hoaDonDouble;
    }

    string getQuyenDoiTra() const override {
        return "Co";
    }

    void nhapThongTin() override {
        KhachHang::nhapThongTin();
        cout << "Phi phuc vu: ";
        cin >> phiPhucVu;
    }
};

int main() {
    int n;
    double giaVe;
    cout << "Nhap so luong khach hang: ";
    cin >> n;
    cout << "Nhap gia ve co ban: ";
    cin >> giaVe;

    KhachHang* khachHangs[100];

    for (int i = 0; i < n; i++) {
        string loaiVe;
        cout << "\nNhap thong tin khach hang " << (i + 1) << ":" << endl;
        cout << "Loai ve (Thuong/KM/VIP): ";
        cin >> loaiVe;

        if (loaiVe == "Thuong") {
            khachHangs[i] = new VeThuong("", "", 1, giaVe);
        }
        else if (loaiVe == "KM") {
            khachHangs[i] = new VeKM("", "", 1, giaVe);
        }
        else if (loaiVe == "VIP") {
            khachHangs[i] = new VeVIP("", "", 1, giaVe);
        }
        else {
            cout << "Loai ve khong hop le. Bo qua khach hang nay." << endl;
            khachHangs[i] = nullptr;
            continue;
        }

        cin >> *khachHangs[i];
    }

    cout << "\n" << left << setw(3) << "STT" << "   "
        << left << setw(15) << "Loai ve"
        << left << setw(15) << "Ho ten"
        << left << setw(15) << "So dien thoai"
        << left << setw(15) << "So ve"
        << left << setw(15) << "Hoa don"
        << left << setw(10) << "Quyen doi tra" << endl;
    cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;

    for (int i = 0; i < n; i++) {
        if (khachHangs[i] != nullptr) {
            cout << left << setw(3) << (i + 1) << "   ";
            cout << *khachHangs[i] << endl;
            delete khachHangs[i];
        }
    }

    return 0;
}
