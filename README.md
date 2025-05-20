Họ và tên : Phạm Văn Duy

Mã sinh viên : 24021453

Giới thiệu chủ đề game : Một game 2D đơn giản nơi bạn xả stress khi mất kết nối mạng,
bạn phải vượt qua các chướng ngại để sống sót. Game viết bằng SDL2 và code c++.

Ngưỡng điểm mong muốn : 7,5 - 8

Các tính năng trong game :

-Texture

-Background

-Event bàn phím

-Event chuột

-Animation

-Xử lý va chạm

-Sound

-Background music

-Menu

-Resum

-Status bar

Hình ảnh minh họa :
![image](https://github.com/user-attachments/assets/c09553c9-dbbb-4b5f-bdce-42c4e17016e5)

![image](https://github.com/user-attachments/assets/f954322a-5a98-4057-b3d5-ee8df2fa2672)

![image](https://github.com/user-attachments/assets/58b0de4b-9e23-493f-8c51-d74250ad0c05)


Một số nguyên lý hoạt động :

1. Xử lý va chạm :
   Nguyên Lý : Dựa trên tọa độ hình chữ nhật (SDL_Rect) của hai vật thể, ta xét xem các góc hoặc cạnh của chúng có nằm trong vùng của nhau không.
   Cách hoạt động :
   -Tính 4 cạnh của mỗi vật thể (left, right, top, bottom).

   -Kiểm tra xem cạnh của object1 nằm trong vùng của object2, và ngược lại.
                    
   -Nếu có bất kỳ góc nào của hình này nằm trong hình kia → va chạm xảy ra.

2. Xử lý nhân vật nhảy :

   Nguyên lý: Dựa vào phương trình bậc 2 : y = Yo + Vo*t + 1/2 * a * t^2.

Các nguồn tham khảo :
- Tài liệu lập trình nâng cao
- https://lazyfoo.net/tutorials/SDL/
- Hình ảnh và âm thanh : https://opengameart.org/, canva, ...
- Trong quá trình làm game, mình gặp nhiều bug khó và chưa có kinh nghiệm debug nên sử dụng AI support. Ví dụ: khó khăn trong việc xử lý quá trình vẽ và xóa ảnh khi game chạy sao cho mượt.
  
                    



