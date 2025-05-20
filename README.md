__Họ và tên__ : Phạm Văn Duy

__Mã sinh viên__ : 24021453

__Giới thiệu chủ đề game__ : Một game 2D đơn giản nơi bạn xả stress khi mất kết nối mạng,
bạn phải vượt qua các chướng ngại để sống sót. Game viết bằng SDL2 và code c++.

__Ngưỡng điểm mong muốn__ : 7,5 - 8

##__Các tính năng trong game__ :

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

##__Hình ảnh minh họa__ :
![image](https://github.com/user-attachments/assets/c09553c9-dbbb-4b5f-bdce-42c4e17016e5)

![image](https://github.com/user-attachments/assets/f954322a-5a98-4057-b3d5-ee8df2fa2672)

![image](https://github.com/user-attachments/assets/58b0de4b-9e23-493f-8c51-d74250ad0c05)


##__Một số nguyên lý hoạt động__ :

1. __Xử lý va chạm__ :
 
   __Nguyên Lý__ : Dựa trên tọa độ hình chữ nhật (SDL_Rect) của hai vật thể, ta xét xem các góc hoặc cạnh của chúng có nằm trong vùng của nhau không.
   
   __Cách hoạt động__ :
   - Tính 4 cạnh của mỗi vật thể (left, right, top, bottom).
   - Kiểm tra xem cạnh của object1 nằm trong vùng của object2, và ngược lại.
   - Nếu có bất kỳ góc nào của hình này nằm trong hình kia → va chạm xảy ra.

4. __Xử lý nhân vật nhảy__ :

   __Nguyên lý__: Dựa vào phương trình bậc 2 : y = Yo + Vo*t + 1/2 * a * t^2.

## __Các nguồn tham khảo__ :
- Tài liệu lập trình nâng cao
- https://lazyfoo.net/tutorials/SDL/
- Hình ảnh và âm thanh : https://opengameart.org/, canva, ...
- Trong quá trình làm game, mình gặp nhiều bug khó và chưa có kinh nghiệm debug nên sử dụng AI support. Ví dụ: khó khăn trong việc xử lý quá trình vẽ và xóa ảnh khi game chạy sao cho mượt.
  
                    



