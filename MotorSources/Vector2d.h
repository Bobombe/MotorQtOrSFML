
#ifndef SRC_MOT_VECTOR2D_H_
#define SRC_MOT_VECTOR2D_H_

class Vector2d {

protected:


public:
    double x;
    double y;

    Vector2d();
    Vector2d(double x, double y);
    virtual ~Vector2d();

    // For calculus
    double getNorm();
    double getAngleInDegree();

    Vector2d &normalize();
    void rotateInDegree(double angleInDegree);

    void toNull();


    /////////////////////////////////////////////////////
    //          Calculus operators                     //
    /////////////////////////////////////////////////////
    // Additions
    // The vector keep orientation and direction but
    // its norm will be equal to (old norm + number)
    Vector2d &operator+=(const double & number);
    // Classic vector addition
    Vector2d &operator+=(const Vector2d & vec);
    // The returned vector keep same orientation and direction than originalvector but
    // its norm will be equal to (original norm + number)
    Vector2d operator+(const double & number);
    // Classic vector addition
    Vector2d operator+(const Vector2d & vec);
    // Subtractions (same as Additions)
    Vector2d &operator-=(const double & number);
    Vector2d &operator-=(const Vector2d & vec);
    Vector2d operator-(const double & number);
    Vector2d operator-(const Vector2d & vec) const;
    Vector2d operator-();
    // Multiplications
    Vector2d &operator*=(const double & number);
    // Vector2d &operator*=(const Vector2d & vec);
    Vector2d operator*(const double & number) const;
    // Scalar product
    double operator*(const Vector2d & vec);
    // Divisions
    Vector2d &operator/=(const double & number);
    // Vector2d &operator/=(const Vector2d & vec);
    Vector2d operator/(const double & number);
    // Vector2d operator/(const Vector2d & vec);

    bool operator==(const Vector2d & vec);
};

#endif /* SRC_MOT_VECTOR2D_H_ */
