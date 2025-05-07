// expected: (-5,2)
RotateCCW90(PT(2,5))

// expected: (5,-2)
RotateCW90(PT(2,5));

// expected: (-5,2)
RotateCCW(PT(2,5),M_PI/2);

// expected: (5,2)
ProjectPointLine(PT(-5,-2), PT(10,4), PT(3,7));

// expected: (5,2) (7.5,3) (2.5,1)
ProjectPointSegment(PT(-5,-2), PT(10,4), PT(3,7))
ProjectPointSegment(PT(7.5,3), PT(10,4), PT(3,7))
ProjectPointSegment(PT(-5,-2), PT(2.5,1), PT(3,7))

// expected: 6.78903
DistancePointPlane(4,-4,3,2,-2,5,-8);

// expected: 1 0 1
LinesParallel(PT(1,1), PT(3,5), PT(2,1), PT(4,5))
LinesParallel(PT(1,1), PT(3,5), PT(2,0), PT(4,5))
LinesParallel(PT(1,1), PT(3,5), PT(5,9), PT(7,13));

// expected: 0 0 1
LinesCollinear(PT(1,1), PT(3,5), PT(2,1), PT(4,5))
LinesCollinear(PT(1,1), PT(3,5), PT(2,0), PT(4,5))
LinesCollinear(PT(1,1), PT(3,5), PT(5,9), PT(7,13));

// expected: 1 1 1 0
SegmentsIntersect(PT(0,0), PT(2,4), PT(3,1), PT(-1,3))
SegmentsIntersect(PT(0,0), PT(2,4), PT(4,3), PT(0,5))
SegmentsIntersect(PT(0,0), PT(2,4), PT(2,-1), PT(-2,1))
SegmentsIntersect(PT(0,0), PT(2,4), PT(5,5), PT(1,7));

// expected: (1,2)
ComputeLineIntersection(PT(0,0), PT(2,4), PT(3,1), PT(-1,3));

// expected: (1,1)
ComputeCircleCenter(PT(-3,4), PT(6,1), PT(4,5));

vector<PT> v({PT(0,0), PT(5,0), PT(5,5), PT(0,5)});

// expected: 1 1 1 0 0
PointInPolygon(v, PT(2,2))
PointInPolygon(v, PT(2,0))
PointInPolygon(v, PT(0,2))
PointInPolygon(v, PT(5,2))
PointInPolygon(v, PT(2,5))

// expected: 0 1 1 1 1
PointOnPolygon(v, PT(2,2))
PointOnPolygon(v, PT(2,0))
PointOnPolygon(v, PT(0,2))
PointOnPolygon(v, PT(5,2))
PointOnPolygon(v, PT(2,5))

// expected: {(1,6)}, {(5,4) (4,5)}, {}, {(4,5) (5,4)}, {}, {(4,5) (5,4)}       
CircleLineIntersection(PT(0,6), PT(2,6), PT(1,1), 5);
CircleLineIntersection(PT(0,9), PT(9,0), PT(1,1), 5);
CircleCircleIntersection(PT(1,1), PT(10,10), 5, 5);
CircleCircleIntersection(PT(1,1), PT(8,8), 5, 5);
CircleCircleIntersection(PT(1,1), PT(4.5,4.5), 10, sqrt(2.0)/2.0);
CircleCircleIntersection(PT(1,1), PT(4.5,4.5), 5, sqrt(2.0)/2.0);

// area = 5.0, centroid = (1.1666666, 1.166666)
vector<PT> p({PT(0,0), PT(5,0), PT(1,1), PT(0,5)});
ComputeCentroid(p), ComputeArea(p);