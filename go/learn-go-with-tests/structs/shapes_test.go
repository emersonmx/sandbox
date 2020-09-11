package structs

import "testing"

func TestPerimeter(t *testing.T) {
	rectangle := Rectangle{10.0, 10.0}
	got := Perimeter(rectangle)
	want := 40.0

	if got != want {
		t.Errorf("got %.2f want %.2f", got, want)
	}
}

func TestArea(t *testing.T) {
	tests := []struct {
		name     string
		expected float64
		given    Shape
	}{
		{name: "rectangles", given: Rectangle{12, 6}, expected: 72.0},
		{name: "circles", given: Circle{10}, expected: 314.1592653589793},
		{name: "triangles", given: Triangle{12, 6}, expected: 36.0},
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			actual := (tt.given.Area())
			if actual != tt.expected {
				t.Errorf("%#v got %g want %g", tt.given, tt.expected, actual)
			}
		})
	}
}
