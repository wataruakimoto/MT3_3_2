#include <Novice.h>
#include <cmath>
#include "imgui.h"

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Matrix4x4 {
	float m[4][4];
};

// 加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {

	Vector3 resultAdd;

	resultAdd.x = v1.x + v2.x;
	resultAdd.y = v1.y + v2.y;
	resultAdd.z = v1.z + v2.z;

	return resultAdd;
}

// 減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {

	Vector3 resultSubtract;

	resultSubtract.x = v1.x - v2.x;
	resultSubtract.y = v1.y - v2.y;
	resultSubtract.z = v1.z - v2.z;

	return resultSubtract;
}

// 積
Vector3 Multiply(float scalar, const Vector3& v) {

	Vector3 resultMultiply;

	resultMultiply.x = v.x * scalar;
	resultMultiply.y = v.y * scalar;
	resultMultiply.z = v.z * scalar;

	return resultMultiply;
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }

// 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 resultMultiply = {};

	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			resultMultiply.m[y][x] = m1.m[y][0] * m2.m[0][x] + m1.m[y][1] * m2.m[1][x] + m1.m[y][2] * m2.m[2][x] + m1.m[y][3] * m2.m[3][x];
		}
	}

	return resultMultiply;
}

// x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {

	Matrix4x4 resultRotateX = { 0.0f };

	resultRotateX.m[0][0] = 1.0f;
	resultRotateX.m[1][1] = std::cosf(radian);
	resultRotateX.m[1][2] = std::sinf(radian);
	resultRotateX.m[2][1] = -std::sinf(radian);
	resultRotateX.m[2][2] = std::cosf(radian);
	resultRotateX.m[3][3] = 1.0f;

	return resultRotateX;
}

// y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {

	Matrix4x4 resultRotateY = { 0.0f };

	resultRotateY.m[0][0] = std::cosf(radian);
	resultRotateY.m[0][2] = -std::sinf(radian);
	resultRotateY.m[1][1] = 1.0f;
	resultRotateY.m[2][0] = std::sinf(radian);
	resultRotateY.m[2][2] = std::cosf(radian);
	resultRotateY.m[3][3] = 1.0f;

	return resultRotateY;
}

// z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {

	Matrix4x4 resultRotateZ = { 0.0f };

	resultRotateZ.m[0][0] = std::cosf(radian);
	resultRotateZ.m[0][1] = std::sinf(radian);
	resultRotateZ.m[1][0] = -std::sinf(radian);
	resultRotateZ.m[1][1] = std::cosf(radian);
	resultRotateZ.m[2][2] = 1.0f;
	resultRotateZ.m[3][3] = 1.0f;

	return resultRotateZ;
}

Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

const char kWindowTitle[] = "LE2B_01_アキモト_ワタル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 a{ 0.2f, 1.0f, 0.0f };
	Vector3 b{ 2.4f, 3.1f, 1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Window");
		ImGui::Text("c : %f, %f, %f", c.x, c.y, c.z);
		ImGui::Text("d : %f, %f, %f", d.x, d.y, d.z);
		ImGui::Text("e : %f, %f, %f", e.x, e.y, e.z);
		ImGui::Text(
			"matrix : \n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2],
			rotateMatrix.m[0][3], rotateMatrix.m[1][0], rotateMatrix.m[1][1],
			rotateMatrix.m[1][2], rotateMatrix.m[1][3], rotateMatrix.m[2][0],
			rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2],
			rotateMatrix.m[3][3]);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
