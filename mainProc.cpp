#include <fstream>
#include <iostream>
#include "sphere.h"
#include "hitable_list.h"

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;

	if (world->hit(r, 0.0f, FLT_MAX, rec))
		return 0.5 * vec3(rec.normal.x() + 1.0f, rec.normal.y() + 1.0f, rec.normal.z() + 1.0f);
	else
	{
		// 레이의 방향벡터를 정규화
		vec3 unit_direction = unit_vector(r.direction());
		// 0 ~ 1범위로 변경
		float t = 0.5f * (unit_direction.y() + 1.0f);

		// 선형 보간
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	string filePath = "result.ppm";
	ofstream writeFile(filePath.data());

	if (writeFile.is_open())
	{
		int nx = 200;
		int ny = 100;

		writeFile << "P3\n" << nx << " " << ny << "\n255\n";

		vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);  // 좌측 아래
		vec3 horizontal(4.0f, 0.0f, 0.0f);            // 총 가로 길이 (-2 ~ 2의 범위)
		vec3 vertical(0.0f, 2.0f, 0.0f);              // 총 세로 길이 (-1 ~ 1의 범위)
		vec3 origin(0.0f, 0.0f, 0.0f);                // 레이의 시작점

		hitable *list[2];
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f);
		list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f);

		hitable * world = new hitable_list(list, 2);

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				// 레이의 방향을 각 픽셀 방향으로 지정
				ray r(origin, lower_left_corner + u * horizontal + v * vertical);

				vec3 p = r.point_at_parameter(2.0f);
				vec3 col = color(r, world);

				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);

				writeFile << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}