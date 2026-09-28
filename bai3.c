#include <stdio.h>
#include <string.h>

#define MAX 100
#define HAN_MUC_CHUAN 14
#define GIA_PHAT_MOI_NGAY 5000

int main() {
    // 1. Khai bao cac mang song song va bien dem
    char maPhieu[MAX][20];
    char maSach[MAX][20];
    int soNgayMuon[MAX];
    int soLuong = 0;

    int luaChon;

    // 2. Vong lap Menu dieu khien chuong trinh
    do {
        printf("\n================ HET THONG QUAN LY MUON TRA SACH (LOGISTICS) ================\n");
        printf("1. Them moi phieu muon sach (Create)\n");
        printf("2. Hien thi danh sach phieu muon & Tien phat qua han (Read)\n");
        printf("3. Cap nhat so ngay muon sach (Update)\n");
        printf("4. Xac nhan tra sach / Xoa phieu muon (Delete)\n");
        printf("5. Thoat chuong trinh\n");
        printf("===========================================================================\n");
        printf("Lua chon cua ban (1-5): ");

        if (scanf("%d", &luaChon) != 1) {
            while (getchar() != '\n'); // Don sach bo dem neu nhap ky tu khong phai so
            printf("Lua chon khong hop le, vui long chon lai!\n");
            continue;
        }
        while (getchar() != '\n'); // Don sach ky tu xuong dong sau khi doc so

        switch (luaChon) {
            case 1: {
                printf("\n--- THEM MOI PHIEU MUON ---\n");
                if (soLuong >= MAX) {
                    printf("Bo nho danh sach da day, khong the them moi!\n");
                    break;
                }

                char tempMaPhieu[20];
                printf("Nhap ma phieu: ");
                scanf("%19s", tempMaPhieu);
                while (getchar() != '\n');

                // Kiem tra trung lap ma phieu
                int daTonTai = 0;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], tempMaPhieu) == 0) {
                        daTonTai = 1;
                        break;
                    }
                }

                if (daTonTai) {
                    printf("Ma phieu da ton tai trong he thong!\n");
                    break;
                }

                // Luu ma phieu hop le
                strcpy(maPhieu[soLuong], tempMaPhieu);

                // Nhap ma sach
                printf("Nhap ma sach: ");
                scanf("%19s", maSach[soLuong]);
                while (getchar() != '\n');

                // Nhap so ngay muon (soNgayMuon > 0)
                int ngay = 0;
                do {
                    printf("Nhap so ngay muon: ");
                    if (scanf("%d", &ngay) != 1) {
                        while (getchar() != '\n');
                        printf("Loi: Vui long nhap mot so nguyen hop le!\n");
                        continue;
                    }
                    while (getchar() != '\n');

                    if (ngay <= 0) {
                        printf("Loi: So ngay muon phai lon hon 0!\n");
                    }
                } while (ngay <= 0);

                soNgayMuon[soLuong] = ngay;
                soLuong++;

                printf("Them moi phieu muon thanh cong!\n");
                break;
            }

            case 2: {
                printf("\n================================ DANH SACH PHIEU MUON ================================\n");
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    printf("======================================================================================\n");
                    break;
                }

                printf("%-4s | %-12s | %-12s | %-9s | %-12s | %-15s\n", 
                       "STT", "MA PHIEU", "MA SACH", "SO NGAY", "TRANG THAI", "TIEN PHAT (VND)");
                printf("--------------------------------------------------------------------------------------\n");

                for (int i = 0; i < soLuong; i++) {
                    int tienPhat = 0;
                    char trangThai[15];

                    if (soNgayMuon[i] > HAN_MUC_CHUAN) {
                        int ngayQuaHan = soNgayMuon[i] - HAN_MUC_CHUAN;
                        tienPhat = ngayQuaHan * GIA_PHAT_MOI_NGAY;
                        strcpy(trangThai, "QUA HAN");
                    } else {
                        strcpy(trangThai, "DUNG HAN");
                    }

                    printf("%-4d | %-12s | %-12s | %-9d | %-12s | %-15d\n", 
                           i + 1, maPhieu[i], maSach[i], soNgayMuon[i], trangThai, tienPhat);
                }

                printf("======================================================================================\n");
                break;
            }

            case 3: {
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                char timMa[20];
                printf("Nhap ma phieu can cap nhat: ");
                scanf("%19s", timMa);
                while (getchar() != '\n');

                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu trong he thong!\n");
                } else {
                    printf("So ngay muon hien tai cua phieu %s la: %d\n", maPhieu[pos], soNgayMuon[pos]);
                    
                    int ngayMoi = 0;
                    do {
                        printf("Nhap so ngay muon moi: ");
                        if (scanf("%d", &ngayMoi) != 1) {
                            while (getchar() != '\n');
                            printf("Loi: Vui long nhap mot so nguyen hop le!\n");
                            continue;
                        }
                        while (getchar() != '\n');

                        if (ngayMoi <= 0) {
                            printf("Loi: So ngay muon phai lon hon 0!\n");
                        }
                    } while (ngayMoi <= 0);

                    soNgayMuon[pos] = ngayMoi;
                    printf("Cap nhat so ngay muon thanh cong!\n");
                }
                break;
            }

            case 4: {
                if (soLuong == 0) {
                    printf("Danh sach phieu muon hien dang rong!\n");
                    break;
                }

                char timMa[20];
                printf("Nhap ma phieu xac nhan tra/xoa: ");
                scanf("%19s", timMa);
                while (getchar() != '\n');

                int pos = -1;
                for (int i = 0; i < soLuong; i++) {
                    if (strcmp(maPhieu[i], timMa) == 0) {
                        pos = i;
                        break;
                    }
                }

                if (pos == -1) {
                    printf("Khong tim thay ma phieu can xoa!\n");
                } else {
                    // Don mang tu vi tri pos den soLuong - 2
                    for (int i = pos; i < soLuong - 1; i++) {
                        strcpy(maPhieu[i], maPhieu[i + 1]);
                        strcpy(maSach[i], maSach[i + 1]);
                        soNgayMuon[i] = soNgayMuon[i + 1];
                    }
                    soLuong--;
                    printf("Xac nhan tra sach va xoa phieu muon thanh cong!\n");
                }
                break;
            }

            case 5:
                printf("\nDa thoat chuong trinh quan ly LIBRARY_WMS Logistics Subsystem. Tam biet!\n");
                break;

            default:
                printf("Lua chon khong hop le, vui long chon lai!\n");
                break;
        }

    } while (luaChon != 5);

    return 0;
}