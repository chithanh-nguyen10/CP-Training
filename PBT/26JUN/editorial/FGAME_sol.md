**Preresquisites.** Grundy, guess-force

## FGAME
Một hướng làm đơn giản dùng quy hoạch động để tính các trạng thái thắng/thua cho bài này, nhưng cách đó không thể tổng quát cho bài FGAME2, nên ở đây mình sẽ giới thiệu hướng làm sử dụng hàm grundy.

### Subtask 1. $n,m \leq 100$

Gọi $\texttt{grundy}[i][j]$ là giá trị grundy của trạng thái trò chơi khi chỉ còn $i$ hàng đầu tiên và $j$ cột đầu tiên.

Hiển nhiên khi không còn ô nào xóa thì đó là trạng thái thua, dẫn đến grundy của các trạng thái đó bằng 0. Từ đó có các base cases là $\texttt{grundy}[0][j] = \texttt{grundy}[i][0] = 0$.

Khi tính $\texttt{grundy}[i][j]$ ta duyệt tất cả các nước đi hợp lệ: xóa một số hàng cuối hoặc xóa một số cột cuối. Tính hợp lệ của mỗi nước đi được kiểm tra bằng mảng cộng dồn. Với mỗi trạng thái đó, đánh dấu các giá trị grundy lại, tính mex của chúng để suy ra $\texttt{grundy}[i][j]$.

Có $O(n\times m)$ trạng thái grundy cần tính và chi phí transition là $O(n+m)$ nên độ phức tạp thuật toán là $O((n + m)\times n \times m)$.

### Subtask 2. $n,m \leq 1000$
Ta có nhận xét quan trọng là $\texttt{grundy}[i][j] \in \\{0, 1, 2\\} \ (\textrm{*})$, chứng minh ở phần sau.

Vì giá trị grundy rất nhỏ, ta không cần lưu toàn bộ các trạng thái chuyển tiếp. Với mỗi hàng và mỗi cột, ta lưu một mask biểu diễn các giá trị Grundy đã xuất hiện ứng với từng giá trị tổng cộng dồn modulo $3$.

Khi tính $\texttt{grundy}[i][j]$, dựa vào cộng dồn modulo 3, ta có thể tính được mask chứa các giá trị grundy của các trạng thái trước. Từ mask này, ta có thể suy ra mex của chúng.

Độ phức tạp lúc này chỉ còn $O(n\times m)$ do chi phí transiton chỉ còn $O(1)$ khi sử dụng bitwise operators.

## FGAME2
Lúc này, trò chơi được mở rộng từ một $1$ thành $4$ bảng. Gọi $4$ trò chơi tương ứng với bốn bảng là $G_1, G_2, G_3, G_4$ và trò chơi hiện tại là $G$. Khi đó, trò chơi đang xét chính là trò chơi tổng của bốn trò chơi này.

Theo định lý Sprague–Grundy, giá trị grundy của trò chơi tổng bằng xor của các giá trị grundy của các trò chơi thành phần, hay:
$$
\texttt{grundy}(G) = \texttt{grundy}(G_1) \oplus \texttt{grundy}(G_2) \oplus \texttt{grundy}(G_3) \oplus \texttt{grundy}(G_4)
$$

Vì thế bài toán quy về giải bài FGAME cho tất cả các bảng.

### Chứng minh nhận xét $(\textrm{*})$
Gọi $S[i][j]$ là mảng cộng dồn của mảng ban đầu **khi modulo $3$**, ta có kết quả mạnh hơn là:
- Nếu $S[i][j] = 0$ thì $\texttt{grundy}[i][j] \in \\{0, 1\\}$