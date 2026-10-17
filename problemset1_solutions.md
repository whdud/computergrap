# Computer Graphics — Problem Set 1 풀이

> 표기: 동차좌표는 열벡터, 변환은 행렬을 **왼쪽에서** 곱한다 (P' = M·P).
> 회전의 양의 방향은 반시계(CCW, 오른손 법칙).

---

## 1. 원근 투영 (COP = 원점, viewing face z = −6)

카메라는 원점에서 −z 방향을 본다. 점 P(x, y, z)와 원점을 잇는 직선이 viewing face(z = −6)와 만나는 점이 투영점이다.
원점–P'–(0,0,−6) 이 이루는 삼각형과 원점–P–(0,0,z) 가 이루는 삼각형은 **닮음**이므로

$$\frac{x'}{x} = \frac{y'}{y} = \frac{z'}{z} = \frac{-6}{z}
\quad\Rightarrow\quad x' = x\cdot\frac{-6}{z},\; y' = y\cdot\frac{-6}{z},\; z' = -6$$

### a) P = (15, −20, −30)

비율 = (−6)/(−30) = 1/5

- x' = 15 · 1/5 = **3**
- y' = −20 · 1/5 = **−4**
- z' = **−6**

**P' = (3, −4, −6)**

### b) Q = (15, −20, −60)

비율 = (−6)/(−60) = 1/10

- x' = 15 · 1/10 = 1.5, y' = −20 · 1/10 = −2

**Q' = (1.5, −2, −6)**

**차이가 나는 이유 (원근 투영 원리)**
원근 투영에서 투영점은 x, y를 깊이 |z|로 **나눈다** (x' = −near·x/z). 즉 투영 크기는 카메라(COP)로부터의 거리에 반비례한다.
Q는 P보다 카메라에서 2배 멀리 있으므로 (|z| = 60 vs 30) 투영된 좌표가 정확히 1/2로 줄어들어 viewing face의 중심(0, 0, −6)에 더 가까이 찍힌다.
모든 투영선이 하나의 점(COP)으로 모이기 때문에 생기는 현상이며, 이것이 "멀리 있는 물체는 작게 보인다"는 원근감(foreshortening)이다. 투영선이 서로 평행한 직교 투영이었다면 P와 Q는 같은 점에 투영되었을 것이다.

---

## 2. 2D 복합 변환, P = (4, 2)

### a) 각 단계의 3×3 행렬

x-shear (h = 0.5): x' = x + hy, y' = y

$$M_{shear}=\begin{bmatrix}1&0.5&0\\0&1&0\\0&0&1\end{bmatrix}$$

CCW 90° 회전 (cos 90° = 0, sin 90° = 1)

$$M_{rot}=\begin{bmatrix}\cos90^\circ&-\sin90^\circ&0\\\sin90^\circ&\cos90^\circ&0\\0&0&1\end{bmatrix}=\begin{bmatrix}0&-1&0\\1&0&0\\0&0&1\end{bmatrix}$$

평행이동 (3, −1)

$$M_{trans}=\begin{bmatrix}1&0&3\\0&1&-1\\0&0&1\end{bmatrix}$$

### b) 복합 행렬

열벡터 표현에서는 먼저 적용되는 변환이 점에 가장 가까운 **오른쪽**에 온다.

$$M_{total}=M_{trans}\cdot M_{rot}\cdot M_{shear}$$

먼저 M_rot · M_shear:

$$\begin{bmatrix}0&-1&0\\1&0&0\\0&0&1\end{bmatrix}\begin{bmatrix}1&0.5&0\\0&1&0\\0&0&1\end{bmatrix}=\begin{bmatrix}0&-1&0\\1&0.5&0\\0&0&1\end{bmatrix}$$

그 다음 M_trans를 왼쪽에 곱한다:

$$M_{total}=\begin{bmatrix}1&0&3\\0&1&-1\\0&0&1\end{bmatrix}\begin{bmatrix}0&-1&0\\1&0.5&0\\0&0&1\end{bmatrix}=\begin{bmatrix}0&-1&3\\1&0.5&-1\\0&0&1\end{bmatrix}$$

### c) P' 계산

$$\begin{bmatrix}0&-1&3\\1&0.5&-1\\0&0&1\end{bmatrix}\begin{bmatrix}4\\2\\1\end{bmatrix}=\begin{bmatrix}0\cdot4-1\cdot2+3\\1\cdot4+0.5\cdot2-1\\1\end{bmatrix}=\begin{bmatrix}1\\4\\1\end{bmatrix}$$

**P' = (1, 4)**

검산 (단계별): shear → (4+0.5·2, 2) = (5, 2) → 회전 → (−2, 5) → 이동 → (1, 4) ✔

---

## 3. 3D 복합 변환, P = (1, 2, 3)

### a) 각 단계의 4×4 행렬

x-shear (h = 2, y에 따라, z 영향 없음): x' = x + 2y

$$M_{shear}=\begin{bmatrix}1&2&0&0\\0&1&0&0\\0&0&1&0\\0&0&0&1\end{bmatrix}$$

y축 기준 CCW 90° 회전: x' = x cosθ + z sinθ, z' = −x sinθ + z cosθ

$$M_{rot}=\begin{bmatrix}\cos\theta&0&\sin\theta&0\\0&1&0&0\\-\sin\theta&0&\cos\theta&0\\0&0&0&1\end{bmatrix}=\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}$$

평행이동 (−3, 0, 5)

$$M_{trans}=\begin{bmatrix}1&0&0&-3\\0&1&0&0\\0&0&1&5\\0&0&0&1\end{bmatrix}$$

### b) 복합 행렬

$$M_{total}=M_{trans}\cdot M_{rot}\cdot M_{shear}$$

M_rot · M_shear:

$$\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}1&2&0&0\\0&1&0&0\\0&0&1&0\\0&0&0&1\end{bmatrix}=\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&-2&0&0\\0&0&0&1\end{bmatrix}$$

M_trans를 왼쪽에 곱하면 마지막 열에 이동량이 더해진다:

$$M_{total}=\begin{bmatrix}0&0&1&-3\\0&1&0&0\\-1&-2&0&5\\0&0&0&1\end{bmatrix}$$

### c) P' 계산

$$M_{total}\begin{bmatrix}1\\2\\3\\1\end{bmatrix}=\begin{bmatrix}0+0+3-3\\0+2+0+0\\-1-4+0+5\\1\end{bmatrix}=\begin{bmatrix}0\\2\\0\\1\end{bmatrix}$$

**P' = (0, 2, 0)**

검산: shear → (1+2·2, 2, 3) = (5, 2, 3) → Ry(90°) → (z, y, −x) = (3, 2, −5) → 이동 → (0, 2, 0) ✔

---

## 4. glFrustum(left, right, bottom, top, near, far)

### a) near / far 평면의 z 좌표
카메라가 원점에서 −z 방향을 보므로 두 평면은 음의 z 쪽에 있다.

- near 평면: **z = −near**
- far 평면: **z = −far**

### b) near, far 가 양수인 이유
near, far는 좌표값이 아니라 **카메라로부터 시선 방향(−z)으로 잰 거리**이다. 시선 방향이 −z이므로 카메라 앞에 있는 점들은 모두 z < 0이고, 거리로 표현하면 양수가 된다 (실제 위치는 z = −near, −far).
- near ≤ 0 이면 평면이 카메라 위치나 카메라 뒤에 놓여 원근 나눗셈(÷|z|)이 정의되지 않거나 (z = 0에서 0으로 나눔) 뒤쪽 물체가 뒤집혀 투영된다.
- 따라서 0 < near < far 여야 카메라 **앞쪽**의 유효한 절두체가 정의된다.

### c) z축 대칭 절두체 조건
- **left = −right**, right > 0 (크기는 같고 부호만 반대)
- **bottom = −top**, top > 0 (크기는 같고 부호만 반대)

이때 near 평면의 중심이 (0, 0, −near)로 z축(시선축) 위에 놓여 시야가 상하좌우 균형을 이룬다.

---

## 5. 2D 반사 변환

### a)

$$M_{rx}=\begin{bmatrix}1&0&0\\0&-1&0\\0&0&1\end{bmatrix}\;(x,y)\to(x,-y),\qquad
M_{ry}=\begin{bmatrix}-1&0&0\\0&1&0\\0&0&1\end{bmatrix}\;(x,y)\to(-x,y)$$

### b) M_total = R_180 · M_rx

$$R_{180}=\begin{bmatrix}\cos180^\circ&-\sin180^\circ&0\\\sin180^\circ&\cos180^\circ&0\\0&0&1\end{bmatrix}=\begin{bmatrix}-1&0&0\\0&-1&0\\0&0&1\end{bmatrix}$$

M_rx를 먼저 적용하므로 오른쪽에 둔다:

$$M_{total}=R_{180}\cdot M_{rx}=\begin{bmatrix}-1&0&0\\0&-1&0\\0&0&1\end{bmatrix}\begin{bmatrix}1&0&0\\0&-1&0\\0&0&1\end{bmatrix}=\begin{bmatrix}-1&0&0\\0&1&0\\0&0&1\end{bmatrix}$$

### c) P(3, 5)에 적용

$$M_{total}\begin{bmatrix}3\\5\\1\end{bmatrix}=\begin{bmatrix}-3\\5\\1\end{bmatrix}\quad\Rightarrow\quad P'=(-3,5)$$

y축 대칭만 적용한 경우:

$$M_{ry}\begin{bmatrix}3\\5\\1\end{bmatrix}=\begin{bmatrix}-3\\5\\1\end{bmatrix}$$

M_total = M_ry 이므로 (행렬 자체가 같음) 모든 점에 대해 결과가 같다. 즉 **x축 반사 후 180° 회전 = y축 반사**이다.

---

## 6. near = 3, far = 18, near 평면 −2 ≤ x ≤ 2, −1 ≤ y ≤ 1

(glFrustum(−2, 2, −1, 1, 3, 18)과 같음)

### a) near / far 평면

| | z 좌표 | x 범위 | y 범위 | 가로 | 세로 |
|---|---|---|---|---|---|
| near | **−3** | [−2, 2] | [−1, 1] | **4** | **2** |
| far | **−18** | [−12, 12] | [−6, 6] | **24** | **12** |

far 평면 크기: 닮음비 = far / near = 18 / 3 = 6
- x: ±2 × 6 = ±12 → 가로 24
- y: ±1 × 6 = ±6 → 세로 12

꼭짓점:
- near: (±2, ±1, −3)
- far: (±12, ±6, −18)

```
            y
            |        far (z=-18)
            |   (-12,6,-18) ┌────────────────────┐ (12,6,-18)
            |               │                    │
            |   near (z=-3) │   (-2,1,-3)┌──┐(2,1,-3)
   COP(0,0,0)● ─ ─ ─ ─ ─ ─ ─│─ ─ ─ ─ ─ ─ │  │ ─ ─ ─ ─ ─ → -z (시선)
            |               │  (-2,-1,-3)└──┘(2,-1,-3)
            |               │                    │
            |  (-12,-6,-18) └────────────────────┘ (12,-6,-18)
```
(원점에서 near 사각형의 네 모서리를 지나는 네 직선이 far 사각형의 네 모서리에 닿는 사각뿔대)

### b) viewing face(z = −3)로의 투영

x' = x · (−3)/z, y' = y · (−3)/z, z' = −3

- P = (4, 2, −9): 비율 = −3/−9 = 1/3 → **P' = (4/3, 2/3, −3) ≈ (1.33, 0.67, −3)**
- Q = (−2, 1, −6): 비율 = −3/−6 = 1/2 → **Q' = (−1, 0.5, −3)**

두 투영점 모두 −2 ≤ x ≤ 2, −1 ≤ y ≤ 1 안에 있고 깊이도 3 ≤ |z| ≤ 18 이므로 화면에 보인다.

---

## 7. 직사각형 A(0,0), B(4,0), C(4,2), D(0,2)

### a) x-shear (h = 1/2)

x' = x + ½y, y' = y

$$S_x=\begin{bmatrix}1&1/2&0\\0&1&0\\0&0&1\end{bmatrix}$$

| 점 | 계산 | 결과 |
|---|---|---|
| A(0,0) | (0+0, 0) | **(0, 0)** |
| B(4,0) | (4+0, 0) | **(4, 0)** |
| C(4,2) | (4+1, 2) | **(5, 2)** |
| D(0,2) | (0+1, 2) | **(1, 2)** |

```
 y
 2 |   D'(1,2)───────────C'(5,2)
   |   /                 /
 1 |  /                 /
   | /                 /
 0 A'(0,0)──────────B'(4,0)──── x
   0   1   2   3   4   5
```
아랫변은 고정되고 윗변이 오른쪽으로 1만큼 밀린 평행사변형.

### b) 이어서 y-shear (g = −2)

x' = x, y' = y + gx = y − 2x

$$S_y=\begin{bmatrix}1&0&0\\-2&1&0\\0&0&1\end{bmatrix}$$

합성 행렬 (S_x 먼저 → 오른쪽):

$$M=S_y\cdot S_x=\begin{bmatrix}1&0&0\\-2&1&0\\0&0&1\end{bmatrix}\begin{bmatrix}1&1/2&0\\0&1&0\\0&0&1\end{bmatrix}=\begin{bmatrix}1&1/2&0\\-2&0&0\\0&0&1\end{bmatrix}$$

(두 번째 행: −2·1 + 1·0 = −2, −2·½ + 1·1 = 0)

최종 꼭짓점 (x'' = x + ½y, y'' = −2x):

| 점 | a) 결과에 y-shear | M으로 직접 | 최종 |
|---|---|---|---|
| A | (0, 0 − 0) | (0, 0) | **(0, 0)** |
| B | (4, 0 − 8) | (4, −8) | **(4, −8)** |
| C | (5, 2 − 10) | (4+1, −8) | **(5, −8)** |
| D | (1, 2 − 2) | (0+1, 0) | **(1, 0)** |

---

## 8. Rx(90°), Ry(90°), P = (1, −2, 3)

$$R_x=\begin{bmatrix}1&0&0&0\\0&0&-1&0\\0&1&0&0\\0&0&0&1\end{bmatrix}\;(x,y,z)\to(x,-z,y),\qquad
R_y=\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}\;(x,y,z)\to(z,y,-x)$$

### 경우 1: Rx 먼저, 그 다음 Ry → M₁ = Ry · Rx

$$M_1=\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}1&0&0&0\\0&0&-1&0\\0&1&0&0\\0&0&0&1\end{bmatrix}=\begin{bmatrix}0&1&0&0\\0&0&-1&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}$$

$$M_1\begin{bmatrix}1\\-2\\3\\1\end{bmatrix}=\begin{bmatrix}-2\\-3\\-1\\1\end{bmatrix}$$

단계별: Rx → (1, −3, −2) → Ry → (−2, −3, −1). **결과 (−2, −3, −1)**

### 경우 2: Ry 먼저, 그 다음 Rx → M₂ = Rx · Ry

$$M_2=\begin{bmatrix}1&0&0&0\\0&0&-1&0\\0&1&0&0\\0&0&0&1\end{bmatrix}\begin{bmatrix}0&0&1&0\\0&1&0&0\\-1&0&0&0\\0&0&0&1\end{bmatrix}=\begin{bmatrix}0&0&1&0\\1&0&0&0\\0&1&0&0\\0&0&0&1\end{bmatrix}$$

$$M_2\begin{bmatrix}1\\-2\\3\\1\end{bmatrix}=\begin{bmatrix}3\\1\\-2\\1\end{bmatrix}$$

단계별: Ry → (3, −2, −1) → Rx → (3, 1, −2). **결과 (3, 1, −2)**

두 결과가 다르므로 **3D 회전은 일반적으로 교환법칙이 성립하지 않는다** (Ry·Rx ≠ Rx·Ry).

---

## 9. P(2, 3, 1) → P'(2, −1, 3)인 회전

### 회전축 판단
- x 좌표: 2 → 2 (불변)
- y: 3 → −1, z: 1 → 3 (변함)

회전축 위의 좌표 성분은 회전해도 변하지 않으므로 **x축** 회전이다.
추가 근거: 회전은 축에 수직인 평면에서의 거리를 보존한다. yz 평면에서 √(3²+1²) = √10 = √((−1)²+3²) ✔.
(y축이면 y가, z축이면 z가 보존되어야 하는데 둘 다 변하므로 불가능.)

### 회전각
x축 회전 공식: y' = y cosθ − z sinθ, z' = y sinθ + z cosθ

$$\begin{cases}3\cos\theta-\sin\theta=-1\\3\sin\theta+\cos\theta=3\end{cases}$$

첫째 식에서 sinθ = 3cosθ + 1을 둘째 식에 대입:
3(3cosθ + 1) + cosθ = 3 → 10cosθ = 0 → **cosθ = 0**, sinθ = 1

0° ≤ θ < 360°에서 cosθ = 0, sinθ = 1 → **θ = 90°**

검산: y' = 3·0 − 1·1 = −1, z' = 3·1 + 1·0 = 3 ✔

---

## 10. gluPerspective(60.0, 2.0, 10.0, 100.0)

fovy = 60°이고 z축 기준 대칭이므로 시선축에서 위쪽 30°, 아래쪽 30°.
그림 3.32와 같이 yz 평면에서 apex–(0,0,−near)–(0,top,−near)가 직각삼각형을 이룬다.

$$\tan\frac{fovy}{2}=\frac{top}{near}\Rightarrow top=near\cdot\tan30^\circ$$

### 1) frustum과 8개 꼭짓점

near 평면 (z = −10):
- top = 10 · tan30° = 10/√3 ≈ **5.774**, bottom = −5.774
- width = aspect × height = 2 × (2 × 5.774) = 23.094 → right = 20/√3 ≈ **11.547**, left = −11.547

far 평면 (z = −100): 닮음비 100/10 = 10
- top = 100/√3 ≈ 57.735, right = 200/√3 ≈ 115.470

| | 꼭짓점 |
|---|---|
| near | (−11.547, −5.774, −10), (11.547, −5.774, −10), (11.547, 5.774, −10), (−11.547, 5.774, −10) |
| far | (−115.470, −57.735, −100), (115.470, −57.735, −100), (115.470, 57.735, −100), (−115.470, 57.735, −100) |

정확한 값: near = (±20/√3, ±10/√3, −10), far = (±200/√3, ±100/√3, −100)

```
 yz 평면 단면 (x = 0)
        y
        |                        ／ (0, 57.735, -100)
        |                   ／
        |  (0,5.774,-10) ／
        |          ／ |
 (0,0,0)●──30°─────────┼──────────────────────── -z
        |   30°  ＼ |
        |          ＼ (0,-5.774,-10)
        |                   ＼
        |                        ＼ (0, -57.735, -100)
```
apex(원점)에서 near 평면의 직사각형(23.09 × 11.55)과 far 평면의 직사각형(230.94 × 115.47)으로 퍼져 나가는 사각뿔대.

### 2) 동일한 glFrustum

$$\texttt{glFrustum}(-\tfrac{20}{\sqrt3},\ \tfrac{20}{\sqrt3},\ -\tfrac{10}{\sqrt3},\ \tfrac{10}{\sqrt3},\ 10,\ 100)$$
$$\approx\texttt{glFrustum}(-11.547,\ 11.547,\ -5.774,\ 5.774,\ 10.0,\ 100.0)$$

구하는 방법 (그림 3.32 참고):
1. near, far는 그대로 사용한다 (10, 100).
2. 그림 3.32처럼 yz 평면 단면을 보면 apex에서 viewing face까지 z 방향 거리는 near = 10이고, 시선축과 frustum 위쪽 모서리 사이 각은 fovy/2 = 30°이다. 직각삼각형에서 top = near · tan(fovy/2) = 10 · tan30° = 10/√3. 대칭이므로 bottom = −top.
   (예시 glFrustum(−5,5,−5,5,5,100)에서는 거꾸로 tan⁻¹(5/5) = 45° → fovy = 90°였다.)
3. aspect = width / height 이므로 width = aspect · height = 2 · (20/√3) = 40/√3. 대칭이므로 right = width/2 = 20/√3, left = −right.

일반식: top = near·tan(fovy/2), bottom = −top, right = aspect·top, left = −right.
