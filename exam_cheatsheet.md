# 시험 대비 핵심 공식 요약

## 1. 변환 행렬 (열벡터, P' = M·P)
| 변환 | 2D (3×3) 핵심 | 3D (4×4) 핵심 |
|---|---|---|
| 이동 | 마지막 열 (tx, ty) | 마지막 열 (tx, ty, tz) |
| x-shear | x' = x + h·y → [1 h; 0 1] | x' = x + h·y (행 0, 열 1에 h) |
| y-shear | y' = y + g·x → [1 0; g 1] | |
| 회전 (CCW) | [c −s; s c] | Rx: y'=yc−zs, z'=ys+zc · Ry: x'=xc+zs, z'=−xs+zc · Rz: 2D와 동일 |
| 반사 | M_rx = diag(1,−1,1), M_ry = diag(−1,1,1) | z 반전 R = diag(1,1,−1,1) |

- **복합 순서**: 먼저 적용하는 변환이 **오른쪽** → M = M₃·M₂·M₁
- 90° 회전 빠른 계산: Rx: (x, −z, y) · Ry: (z, y, −x) · Rz: (−y, x, z)
- 회전 / 행렬 곱은 **교환법칙 X** (Rx·Ry ≠ Ry·Rx)
- R_180 · M_rx = M_ry (x축 반사 후 180° 회전 = y축 반사)
- 회전축 찾기: 변하지 않는 좌표 성분 = 회전축. 연립방정식으로 cosθ, sinθ 구하기

## 2. 원근 투영 / glFrustum
- 카메라: 원점에서 −z 방향. near 평면 z = −near, far 평면 z = −far (near, far > 0은 **거리**)
- 닮음 투영: **x' = x·(−n)/z, y' = y·(−n)/z, z' = −n** → 멀수록 작아짐 (|z|에 반비례)
- far 평면 크기 = near 평면 크기 × (far / near)
- 대칭 frustum: left = −right, bottom = −top
- **gluPerspective(fovy, aspect, n, f) ↔ glFrustum**
  - top = n·tan(fovy/2), bottom = −top
  - right = aspect·top, left = −right
  - 예: (90, 1, 5, 100) ↔ (−5, 5, −5, 5, 5, 100)

## 3. 직교 투영 glOrtho(l, r, b, t, n, f) → CVV [−1,1]³
N = R·S·T =
```
[ 2/(r−l)    0        0       −(r+l)/(r−l) ]
[   0      2/(t−b)    0       −(t+b)/(t−b) ]
[   0        0     −2/(f−n)   −(f+n)/(f−n) ]
[   0        0        0             1      ]
```
- T: 중심 ((l+r)/2, (b+t)/2, −(n+f)/2) → 원점, S: 크기 → 2, R: z 반전 (오른손 → 왼손)
- 검산: z = −n → −1, z = −f → +1
- NDC = clip / w (직교 투영이면 w = 1)

## 4. 뷰포트 glViewport(left, bottom, w, h)
- x' = (w/2)(x_ndc + 1) + left, y' = (h/2)(y_ndc + 1) + bottom
- z_ndc는 깊이 테스트에 쓰려고 보존

## 5. 카메라 / lookAt
1. z_cam = (eye − center) / |eye − center| (카메라는 **−z_cam**을 봄)
2. x_cam = (up × z_cam) / |up × z_cam|
3. y_cam = z_cam × x_cam
4. V = R_cam · T_cam, R_cam의 행 = x_cam, y_cam, z_cam, T_cam = 이동(−eye)
   - V의 마지막 열 = (−x·eye, −y·eye, −z·eye)
- V·eye = 원점, V·center = (0, 0, −|eye−center|)
- eye 좌표 z < 0 → 카메라 앞, z > 0 → 카메라 뒤

## 6. 벡터
- a × b = (a_y b_z − a_z b_y, a_z b_x − a_x b_z, a_x b_y − a_y b_x)
- b × a = −(a × b), (a × b)·a = (a × b)·b = 0, 결합법칙 X: (i×j)×j = −i, i×(j×j) = 0
- i×j = k, j×k = i, k×i = j
- 법선: N = (P2−P1) × (P3−P1), CCW 순서 = 전면 (오른손 법칙)

## 7. 백페이스 컬링
- V = Eye − P (면 → 카메라)
- N·V > 0 → 전면(그림), N·V < 0 → 후면(컬링)

## 8. Z-buffer
- 초기: color = 배경, z = 1.0 (최대 깊이)
- `if (z_new < z_buffer) { color = c_new; z_buffer = z_new; }` ← **z_buffer 갱신 빠뜨리기 주의**
- `<` 이면 같은 깊이에서 **먼저 온 fragment가 이김** (순서에 따라 색 달라짐)

## 9. 행렬 스택 (glPushMatrix / glPopMatrix)
- Push: 현재 CTM 복사해서 저장, Pop: 저장된 CTM으로 복원
- 특정 물체에만 줄 변환은 **Push 뒤에** 호출해야 함
- glTranslate/glScale 호출 순서대로 오른쪽에 곱해짐: CTM = T·S·U, 점에는 U가 가장 먼저 적용
