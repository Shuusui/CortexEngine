#include "..\include\Matrix.h"


Nash::FMatrix::FMatrix(bool bSetToIdentity)
{
	if (bSetToIdentity)
	{
		Matrix[0].X = 1; Matrix[0].Y = 0; Matrix[0].Z = 0; Matrix[0].W = 0;
		Matrix[1].X = 0; Matrix[1].Y = 1; Matrix[1].Z = 0; Matrix[1].W = 0;
		Matrix[2].X = 0; Matrix[2].Y = 0; Matrix[2].Z = 1; Matrix[2].W = 0;
		Matrix[3].X = 0; Matrix[3].Y = 0; Matrix[3].Z = 0; Matrix[3].W = 1;
	}
	else
	{
		Matrix[0] = FVector4();
		Matrix[1] = FVector4();
		Matrix[2] = FVector4();
		Matrix[3] = FVector4();
	}
}

Nash::FMatrix::FMatrix(const float & xx, const float & xy, const float & xz, const float & xw, const float & yx, const float & yy, const float & yz, const float & yw, const float & zx, const float & zy, const float & zz, const float & zw, const float & wx, const float & wy, const float & wz, const float & ww)
{
	Matrix[0] = FVector4(xx, xy, xz, xw);
	Matrix[1] = FVector4(yx, yy, yz, yw); 
	Matrix[2] = FVector4(zx, zy, zz, zw); 
	Matrix[3] = FVector4(wx, wy, wz, ww);
}

Nash::FMatrix::FMatrix(const FVector4 & vec1, const FVector4 & vec2, const FVector4 & vec3, const FVector4 & vec4)
{
	Matrix[0] = vec1; 
	Matrix[1] = vec2; 
	Matrix[2] = vec3; 
	Matrix[3] = vec4; 
}

Nash::FMatrix::FMatrix(const FMatrix & matrix)
{
	Matrix[0] = matrix.Matrix[0];
	Matrix[1] = matrix.Matrix[1]; 
	Matrix[2] = matrix.Matrix[2];
	Matrix[3] = matrix.Matrix[3];

}

void Nash::FMatrix::Identity()
{
	Matrix[0].X = 1; Matrix[0].Y = 0; Matrix[0].Z = 0; Matrix[0].W = 0; 
	Matrix[1].X = 0; Matrix[1].Y = 1; Matrix[1].Z = 0; Matrix[1].W = 0; 
	Matrix[2].X = 0; Matrix[2].Y = 0; Matrix[2].Z = 1; Matrix[2].W = 0; 
	Matrix[3].X = 0; Matrix[3].Y = 0; Matrix[3].Z = 0; Matrix[3].W = 1;
}

Nash::FMatrix Nash::FMatrix::Inverse() const
{
	FMatrix mat(
		(Matrix[1].Y * Matrix[2].Z * Matrix[3].W) - (Matrix[1].Y * Matrix[2].W * Matrix[3].Z) - (Matrix[2].Y * Matrix[1].Z * Matrix[3].W) + (Matrix[2].Y * Matrix[1].W * Matrix[3].Z) + (Matrix[3].Y * Matrix[1].Z * Matrix[2].W) - (Matrix[3].Y * Matrix[1].W * Matrix[2].Z),
		(-Matrix[0].Y * Matrix[2].Z * Matrix[3].W) + (Matrix[0].Y * Matrix[2].W * Matrix[3].Z) + (Matrix[2].Y * Matrix[0].Z * Matrix[3].W) - (Matrix[2].Y * Matrix[0].W * Matrix[3].Z) - (Matrix[3].Y * Matrix[0].Z * Matrix[2].W) + (Matrix[3].Y * Matrix[0].W * Matrix[2].Z),
		(Matrix[0].Y * Matrix[1].Z * Matrix[3].W) - (Matrix[0].Y * Matrix[1].W * Matrix[3].Z) - (Matrix[1].Y * Matrix[0].Z * Matrix[3].W) + (Matrix[1].Y * Matrix[0].W * Matrix[3].Z) + (Matrix[3].Y * Matrix[0].Z * Matrix[1].W) + (Matrix[3].Y * Matrix[0].W * Matrix[1].Z),
		(-Matrix[0].Y * Matrix[1].Z * Matrix[2].W) + (Matrix[0].Y * Matrix[1].W * Matrix[2].Z) + (Matrix[1].Y * Matrix[0].Z * Matrix[2].W) - (Matrix[1].Y * Matrix[0].W * Matrix[2].Z) - (Matrix[2].Y * Matrix[0].Z * Matrix[1].W) + (Matrix[2].Y * Matrix[0].W * Matrix[1].Z),
		(-Matrix[1].X * Matrix[2].Z * Matrix[3].W) + (Matrix[1].X * Matrix[2].W * Matrix[3].Z) + (Matrix[2].X * Matrix[1].Z * Matrix[3].W) - (Matrix[2].X * Matrix[1].W * Matrix[3].Z) - (Matrix[3].X * Matrix[1].Z * Matrix[2].W) + (Matrix[3].X * Matrix[1].W * Matrix[2].Z),
		(Matrix[0].X * Matrix[2].Z * Matrix[3].W) - (Matrix[0].X * Matrix[2].W * Matrix[3].Z) - (Matrix[2].X * Matrix[0].Z * Matrix[3].W) + (Matrix[2].X * Matrix[0].W * Matrix[3].Z) + (Matrix[3].X * Matrix[0].Z * Matrix[2].W) - (Matrix[3].X * Matrix[0].W * Matrix[2].Z),
		(-Matrix[0].X * Matrix[1].Z * Matrix[3].W) + (Matrix[0].X * Matrix[1].W * Matrix[3].Z) + (Matrix[1].X * Matrix[0].Z * Matrix[3].W) - (Matrix[1].X * Matrix[0].W * Matrix[3].Z) - (Matrix[3].X * Matrix[0].Z * Matrix[1].W) + (Matrix[3].X * Matrix[0].W * Matrix[1].Z),
		(Matrix[0].X * Matrix[1].Z * Matrix[2].W) - (Matrix[0].X * Matrix[1].W * Matrix[2].Z) - (Matrix[1].X * Matrix[0].Z * Matrix[2].W) + (Matrix[1].X * Matrix[0].W * Matrix[2].Z) + (Matrix[2].X * Matrix[0].Z * Matrix[1].W) - (Matrix[2].X * Matrix[0].W * Matrix[1].Z),
		(Matrix[1].X * Matrix[2].Y * Matrix[3].W) - (Matrix[1].X * Matrix[2].W * Matrix[3].Y) - (Matrix[2].X * Matrix[1].Y * Matrix[3].W) + (Matrix[2].X * Matrix[1].W * Matrix[3].Y) + (Matrix[3].X * Matrix[1].Y * Matrix[2].W) - (Matrix[2].X * Matrix[1].W * Matrix[2].Y),
		(-Matrix[0].X * Matrix[2].Y * Matrix[3].W) + (Matrix[0].X * Matrix[2].W * Matrix[3].Y) + (Matrix[2].X * Matrix[0].Y * Matrix[3].W) - (Matrix[2].X * Matrix[0].W * Matrix[3].Y) - (Matrix[3].X * Matrix[0].Y * Matrix[2].W) + (Matrix[3].X * Matrix[0].W * Matrix[2].Y),
		(Matrix[0].X * Matrix[1].Y * Matrix[3].W) - (Matrix[0].X * Matrix[1].W * Matrix[3].Y) - (Matrix[1].X * Matrix[0].Y * Matrix[3].W) + (Matrix[1].X * Matrix[0].W * Matrix[3].Y) + (Matrix[3].X * Matrix[0].Y * Matrix[1].W) - (Matrix[3].X * Matrix[0].W * Matrix[1].Y),
		(-Matrix[0].X * Matrix[1].Y * Matrix[2].W) + (Matrix[0].X * Matrix[1].W * Matrix[2].Y) + (Matrix[1].X * Matrix[0].Y * Matrix[2].W) - (Matrix[1].X * Matrix[0].W * Matrix[2].Y) - (Matrix[2].X * Matrix[0].Y * Matrix[1].W) + (Matrix[2].X * Matrix[0].W * Matrix[1].Y),
		(-Matrix[1].X * Matrix[2].Y * Matrix[3].Z) + (Matrix[1].X * Matrix[2].Z * Matrix[3].Y) + (Matrix[2].X * Matrix[1].Y * Matrix[3].Z) - (Matrix[2].X * Matrix[1].Z * Matrix[3].Y) - (Matrix[3].X * Matrix[1].Y * Matrix[2].Z) + (Matrix[3].X * Matrix[1].Z * Matrix[2].Y),
		(Matrix[0].X * Matrix[2].Y * Matrix[3].Z) - (Matrix[0].X * Matrix[2].Z * Matrix[3].Y) - (Matrix[2].X * Matrix[0].Y * Matrix[3].Z) + (Matrix[2].X * Matrix[0].Z * Matrix[3].Y) + (Matrix[3].X * Matrix[0].Y * Matrix[2].Z) - (Matrix[3].X * Matrix[0].Z * Matrix[3].Y),
		(-Matrix[0].X * Matrix[1].Y * Matrix[3].Z) + (Matrix[0].X * Matrix[1].Z * Matrix[3].Y) + (Matrix[1].X * Matrix[0].Y * Matrix[3].Z) - (Matrix[1].X * Matrix[0].Z * Matrix[3].Y) - (Matrix[3].X * Matrix[0].Y * Matrix[1].Z) + (Matrix[3].X * Matrix[0].Z * Matrix[1].Y),
		(Matrix[0].X * Matrix[1].Y * Matrix[2].Z) - (Matrix[0].X * Matrix[1].Z * Matrix[2].Y) - (Matrix[1].X * Matrix[0].Y * Matrix[2].Z) + (Matrix[1].X * Matrix[0].Z * Matrix[2].Y) + (Matrix[2].X * Matrix[0].Y * Matrix[1].Z) - (Matrix[2].X * Matrix[0].Z * Matrix[1].Y)
	);
	double det = Matrix[0].X * mat[0].X + Matrix[0].Y * mat[1].X + Matrix[0].Z * mat[2].X + Matrix[0].W * mat[3].X; 
	if (det < VERYSMALL)
		return FMatrix(false);

	det = 1.0 / det;
	return FMatrix(
		mat[0].X * det, mat[0].Y * det, mat[0].Z * det, mat[0].W * det, 
		mat[1].X * det, mat[1].Y * det, mat[1].Z * det, mat[1].W * det, 
		mat[2].X * det, mat[2].Y * det, mat[2].Z * det, mat[2].W * det, 
		mat[3].X * det, mat[3].Y * det, mat[3].Z * det, mat[3].W *det);
}

float Nash::FMatrix::Determinante() const 
{
	return(
		(Matrix[0].X *((Matrix[1].Y * Matrix[2].Z * Matrix[3].W) + (Matrix[1].Z * Matrix[2].W * Matrix[3].Y) + (Matrix[1].W * Matrix[2].Y * Matrix[3].Z) -
						(Matrix[1].W * Matrix[2].Z * Matrix[3].Y) - (Matrix[1].Z * Matrix[2].Y * Matrix[3].W) - (Matrix[1].Y * Matrix[2].W * Matrix[3].Z))) -
		(Matrix[1].X *((Matrix[0].Y * Matrix[2].Z * Matrix[3].W) + (Matrix[0].Z * Matrix[2].W * Matrix[3].Y) + (Matrix[0].W * Matrix[2].Y * Matrix[2].Z) -
						(Matrix[0].W * Matrix[2].Z * Matrix[3].Y) - (Matrix[0].Z * Matrix[2].Y * Matrix[3].W) - (Matrix[0].Y * Matrix[2].W * Matrix[3].Z))) +
		(Matrix[2].X *((Matrix[0].Y * Matrix[1].Z * Matrix[3].W) + (Matrix[0].Z * Matrix[1].W * Matrix[3].Y) + (Matrix[0].W * Matrix[1].Y * Matrix[3].Z) -
						(Matrix[0].W * Matrix[1].Z * Matrix[3].Y) - (Matrix[0].Z * Matrix[1].Y * Matrix[3].W) - (Matrix[0].Y * Matrix[1].W * Matrix[3].Z)))-
		(Matrix[3].X *((Matrix[0].Y * Matrix[1].Z * Matrix[2].W) + (Matrix[0].Z * Matrix[1].W * Matrix[2].Y) + (Matrix[0].W * Matrix[1].Y * Matrix[2].Z) -
						(Matrix[0].W * Matrix[1].Z * Matrix[2].Y) - (Matrix[0].Z * Matrix[1].Y * Matrix[2].W) - (Matrix[0].Y * Matrix[1].W * Matrix[2].Z)))
		);

}
void Nash::FMatrix::RotateX(const float & x)
{
	
	*this *= FMatrix(1, 0, 0, 0,
		0, cos(x), -sin(x), 0,
		0, sin(x), cos(x), 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::RotateY(const float & y)
{
	
	*this *= FMatrix(cos(y), 0, sin(y), 0,
		0, 1, 0, 0,
		-sin(y), 0, cos(y), 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::RotateZ(const float & z)
{
	
	*this *= FMatrix(cos(z), -sin(z), 0, 0,
		sin(z), cos(z), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::Scale(const FVector3 & scale)
{
	*this *= FMatrix(scale.X, 0, 0, 0,
		0, scale.Y, 0, 0,
		0, 0, scale.Z, 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::ScaleX(const float & x)
{
	*this *= FMatrix(x, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::ScaleY(const float & y)
{
	*this *= FMatrix(1, 0, 0, 0,
		0, y, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::ScaleZ(const float & z)
{
	*this *= FMatrix(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, z, 0,
		0, 0, 0, 1);
}
void Nash::FMatrix::Translate(const FVector3 & translation)
{
	*this *= FMatrix(1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translation.X, translation.Y, translation.Z, 1);
}
void Nash::FMatrix::TranslateX(const float & x)
{
	*this *= FMatrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		x, 0, 0, 1);
}
void Nash::FMatrix::TranslateY(const float & y)
{
	*this *= FMatrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, y, 0, 1);
}
void Nash::FMatrix::TranslateZ(const float & z)
{
	*this *= FMatrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, z, 1);
}
void Nash::FMatrix::operator=(const FMatrix & matrix)
{
	Matrix[0] = matrix.Matrix[0]; Matrix[1] = matrix.Matrix[1]; Matrix[2] = matrix.Matrix[2]; Matrix[3] = matrix.Matrix[3];
}

bool Nash::FMatrix::operator==(const FMatrix & matrix) const
{
	return Matrix[0] == matrix.Matrix[0] && Matrix[1] == matrix.Matrix[1] && Matrix[2] == matrix.Matrix[2] && Matrix[3] == matrix.Matrix[3] ? true : false; 
}

bool Nash::FMatrix::operator!=(const FMatrix & matrix) const
{
	return Matrix[0] != matrix.Matrix[1] || Matrix[1] != matrix.Matrix[1] || Matrix[2] != matrix.Matrix[2] || Matrix[3] != matrix.Matrix[3] ? true : false; 
}

Nash::FMatrix Nash::FMatrix::operator+(const FMatrix & matrix) const
{
	return FMatrix(
		Matrix[0].X + matrix.Matrix[0].X, Matrix[0].Y + matrix.Matrix[0].Y, Matrix[0].Z + matrix.Matrix[0].Z, Matrix[0].W + matrix.Matrix[0].W,
		Matrix[1].X + matrix.Matrix[1].X, Matrix[1].Y + matrix.Matrix[1].Y, Matrix[1].Z + matrix.Matrix[1].Z, Matrix[1].W + matrix.Matrix[1].W,
		Matrix[2].X + matrix.Matrix[2].X, Matrix[2].Y + matrix.Matrix[2].Y, Matrix[2].Z + matrix.Matrix[2].Z, Matrix[2].W + matrix.Matrix[2].W,
		Matrix[3].X + matrix.Matrix[3].X, Matrix[3].Y + matrix.Matrix[3].Y, Matrix[3].Z + matrix.Matrix[3].Z, Matrix[3].W + matrix.Matrix[3].W);
}

Nash::FMatrix Nash::FMatrix::operator-(const FMatrix & matrix) const
{
	return FMatrix(
		Matrix[0].X - matrix.Matrix[0].X, Matrix[0].Y - matrix.Matrix[0].Y, Matrix[0].Z - matrix.Matrix[0].Z, Matrix[0].W - matrix.Matrix[0].W,
		Matrix[1].X - matrix.Matrix[1].X, Matrix[1].Y - matrix.Matrix[1].Y, Matrix[1].Z - matrix.Matrix[1].Z, Matrix[1].W - matrix.Matrix[1].W,
		Matrix[2].X - matrix.Matrix[2].X, Matrix[2].Y - matrix.Matrix[2].Y, Matrix[2].Z - matrix.Matrix[2].Z, Matrix[2].W - matrix.Matrix[2].W,
		Matrix[3].X - matrix.Matrix[3].X, Matrix[3].Y - matrix.Matrix[3].Y, Matrix[3].Z - matrix.Matrix[3].Z, Matrix[3].W - matrix.Matrix[3].W);
}

Nash::FMatrix Nash::FMatrix::operator*(const FMatrix & matrix) const
{
	return FMatrix(
		Matrix[0].X * matrix.Matrix[0].X + Matrix[0].Y * matrix.Matrix[1].X + Matrix[0].Z * matrix.Matrix[2].X + Matrix[0].W * matrix.Matrix[3].X,
		Matrix[0].X * matrix.Matrix[0].Y + Matrix[0].Y * matrix.Matrix[1].Y + Matrix[0].Z * matrix.Matrix[2].Y + Matrix[0].W * matrix.Matrix[3].Y,
		Matrix[0].X * matrix.Matrix[0].Z + Matrix[0].Y * matrix.Matrix[1].Z + Matrix[0].Z * matrix.Matrix[2].Z + Matrix[0].W * matrix.Matrix[3].Z,
		Matrix[0].X * matrix.Matrix[0].W + Matrix[0].Y * matrix.Matrix[1].W + Matrix[0].Z * matrix.Matrix[2].W + Matrix[0].W * matrix.Matrix[3].W,
		Matrix[1].X * matrix.Matrix[0].X + Matrix[1].Y * matrix.Matrix[1].X + Matrix[1].Z * matrix.Matrix[2].X + Matrix[1].W * matrix.Matrix[3].X,
		Matrix[1].X * matrix.Matrix[0].Y + Matrix[1].Y * matrix.Matrix[1].Y + Matrix[1].Z * matrix.Matrix[2].Y + Matrix[1].W * matrix.Matrix[3].Y,
		Matrix[1].X * matrix.Matrix[0].Z + Matrix[1].Y * matrix.Matrix[1].Z + Matrix[1].Z * matrix.Matrix[2].Z + Matrix[1].W * matrix.Matrix[3].Z,
		Matrix[1].X * matrix.Matrix[0].W + Matrix[1].Y * matrix.Matrix[1].W + Matrix[1].Z * matrix.Matrix[2].W + Matrix[1].W * matrix.Matrix[3].W,
		Matrix[2].X * matrix.Matrix[0].X + Matrix[2].Y * matrix.Matrix[1].X + Matrix[2].Z * matrix.Matrix[2].X + Matrix[2].W * matrix.Matrix[3].X,
		Matrix[2].X * matrix.Matrix[0].Y + Matrix[2].Y * matrix.Matrix[1].Y + Matrix[2].Z * matrix.Matrix[2].Y + Matrix[2].W * matrix.Matrix[3].Y,
		Matrix[2].X * matrix.Matrix[0].Z + Matrix[2].Y * matrix.Matrix[1].Z + Matrix[2].Z * matrix.Matrix[2].Z + Matrix[2].W * matrix.Matrix[3].Z,
		Matrix[2].X * matrix.Matrix[0].W + Matrix[2].Y * matrix.Matrix[1].W + Matrix[2].Z * matrix.Matrix[2].W + Matrix[2].W * matrix.Matrix[3].W,
		Matrix[3].X * matrix.Matrix[0].X + Matrix[3].Y * matrix.Matrix[1].X + Matrix[3].Z * matrix.Matrix[2].X + Matrix[3].W * matrix.Matrix[3].X,
		Matrix[3].X * matrix.Matrix[0].Y + Matrix[3].Y * matrix.Matrix[1].Y + Matrix[3].Z * matrix.Matrix[2].Y + Matrix[3].W * matrix.Matrix[3].Y,
		Matrix[3].X * matrix.Matrix[0].Z + Matrix[3].Y * matrix.Matrix[1].Z + Matrix[3].Z * matrix.Matrix[2].Z + Matrix[3].W * matrix.Matrix[3].Z,
		Matrix[3].X * matrix.Matrix[0].W + Matrix[3].Y * matrix.Matrix[1].W + Matrix[3].Z * matrix.Matrix[2].W + Matrix[3].W * matrix.Matrix[3].W
		);
}

Nash::FMatrix Nash::FMatrix::operator/(const FMatrix & matrix) const
{
	return *this * matrix.Inverse();
}

Nash::FVector4 Nash::FMatrix::operator[](const int& value) const
{
	return Matrix[value];
}

void Nash::FMatrix::operator+=(const FMatrix & matrix)
{
	Matrix[0].X += matrix.Matrix[0].X; Matrix[0].Y += matrix.Matrix[0].Y; Matrix[0].Z += matrix.Matrix[0].Z; Matrix[0].W += matrix.Matrix[0].W;
	Matrix[1].X += matrix.Matrix[1].X; Matrix[1].Y += matrix.Matrix[1].Y; Matrix[1].Z += matrix.Matrix[1].Z; Matrix[1].W += matrix.Matrix[1].W;
	Matrix[2].X += matrix.Matrix[2].X; Matrix[2].Y += matrix.Matrix[2].Y; Matrix[2].Z += matrix.Matrix[2].Z; Matrix[2].W += matrix.Matrix[2].W;
	Matrix[3].X += matrix.Matrix[3].X; Matrix[3].Y += matrix.Matrix[3].Y; Matrix[3].Z += matrix.Matrix[3].Z; Matrix[3].W += matrix.Matrix[3].W;
}

void Nash::FMatrix::operator-=(const FMatrix & matrix)
{
	Matrix[0].X -= matrix.Matrix[0].X; Matrix[0].Y -= matrix.Matrix[0].Y; Matrix[0].Z -= matrix.Matrix[0].Z; Matrix[0].W -= matrix.Matrix[0].W;
	Matrix[1].X -= matrix.Matrix[1].X; Matrix[1].Y -= matrix.Matrix[1].Y; Matrix[1].Z -= matrix.Matrix[1].Z; Matrix[1].W -= matrix.Matrix[1].W;
	Matrix[2].X -= matrix.Matrix[2].X; Matrix[2].Y -= matrix.Matrix[2].Y; Matrix[2].Z -= matrix.Matrix[2].Z; Matrix[2].W -= matrix.Matrix[2].W;
	Matrix[3].X -= matrix.Matrix[3].X; Matrix[3].Y -= matrix.Matrix[3].Y; Matrix[3].Z -= matrix.Matrix[3].Z; Matrix[3].W -= matrix.Matrix[3].W;
}

void Nash::FMatrix::operator*=(const FMatrix & matrix)
{
	Matrix[0].X = Matrix[0].X * matrix.Matrix[0].X + Matrix[0].Y * matrix.Matrix[1].X + Matrix[0].Z * matrix.Matrix[2].X + Matrix[0].W * matrix.Matrix[3].X;
	Matrix[0].Y = Matrix[0].X * matrix.Matrix[0].Y + Matrix[0].Y * matrix.Matrix[1].Y + Matrix[0].Z * matrix.Matrix[2].Y + Matrix[0].W * matrix.Matrix[3].Y;
	Matrix[0].Z = Matrix[0].X * matrix.Matrix[0].Z + Matrix[0].Y * matrix.Matrix[1].Z + Matrix[0].Z * matrix.Matrix[2].Z + Matrix[0].W * matrix.Matrix[3].Z;
	Matrix[0].W = Matrix[0].X * matrix.Matrix[0].W + Matrix[0].Y * matrix.Matrix[1].W + Matrix[0].Z * matrix.Matrix[2].W + Matrix[0].W * matrix.Matrix[3].W;
	Matrix[1].X = Matrix[1].X * matrix.Matrix[0].X + Matrix[1].Y * matrix.Matrix[1].X + Matrix[1].Z * matrix.Matrix[2].X + Matrix[1].W * matrix.Matrix[3].X;
	Matrix[1].Y = Matrix[1].X * matrix.Matrix[0].Y + Matrix[1].Y * matrix.Matrix[1].Y + Matrix[1].Z * matrix.Matrix[2].Y + Matrix[1].W * matrix.Matrix[3].Y;
	Matrix[1].Z = Matrix[1].X * matrix.Matrix[0].Z + Matrix[1].Y * matrix.Matrix[1].Z + Matrix[1].Z * matrix.Matrix[2].Z + Matrix[1].W * matrix.Matrix[3].Z;
	Matrix[1].W = Matrix[1].X * matrix.Matrix[0].W + Matrix[1].Y * matrix.Matrix[1].W + Matrix[1].Z * matrix.Matrix[2].W + Matrix[1].W * matrix.Matrix[3].W;
	Matrix[2].X = Matrix[2].X * matrix.Matrix[0].X + Matrix[2].Y * matrix.Matrix[1].X + Matrix[2].Z * matrix.Matrix[2].X + Matrix[2].W * matrix.Matrix[3].X;
	Matrix[2].Y = Matrix[2].X * matrix.Matrix[0].Y + Matrix[2].Y * matrix.Matrix[1].Y + Matrix[2].Z * matrix.Matrix[2].Y + Matrix[2].W * matrix.Matrix[3].Y;
	Matrix[2].Z = Matrix[2].X * matrix.Matrix[0].Z + Matrix[2].Y * matrix.Matrix[1].Z + Matrix[2].Z * matrix.Matrix[2].Z + Matrix[2].W * matrix.Matrix[3].Z;
	Matrix[2].W = Matrix[2].X * matrix.Matrix[0].W + Matrix[2].Y * matrix.Matrix[1].W + Matrix[2].Z * matrix.Matrix[2].W + Matrix[2].W * matrix.Matrix[3].W;
	Matrix[3].X = Matrix[3].X * matrix.Matrix[0].X + Matrix[3].Y * matrix.Matrix[1].X + Matrix[3].Z * matrix.Matrix[2].X + Matrix[3].W * matrix.Matrix[3].X;
	Matrix[3].Y = Matrix[3].X * matrix.Matrix[0].Y + Matrix[3].Y * matrix.Matrix[1].Y + Matrix[3].Z * matrix.Matrix[2].Y + Matrix[3].W * matrix.Matrix[3].Y;
	Matrix[3].Z = Matrix[3].X * matrix.Matrix[0].Z + Matrix[3].Y * matrix.Matrix[1].Z + Matrix[3].Z * matrix.Matrix[2].Z + Matrix[3].W * matrix.Matrix[3].Z;
	Matrix[3].W = Matrix[3].X * matrix.Matrix[0].W + Matrix[3].Y * matrix.Matrix[1].W + Matrix[3].Z * matrix.Matrix[2].W + Matrix[3].W * matrix.Matrix[3].W;
}

void Nash::FMatrix::operator/=(const FMatrix & matrix)
{
	*this *= matrix.Inverse();
}
