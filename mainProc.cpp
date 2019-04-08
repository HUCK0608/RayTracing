#include <fstream>
#include <iostream>
#include <time.h>
#include <random>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include "material.h"

vec3 color(const ray& r, hitable *world, int depth)
{
	hit_record rec;

	if (world->hit(r, 0.001f, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;

		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * color(scattered, world, depth + 1);
		else
			return vec3(0.0f, 0.0f, 0.0f);
	}
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
		int ns = 100;

		writeFile << "P3\n" << nx << " " << ny << "\n255\n";

		hitable *list[4];
		list[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian(vec3(0.8f, 0.3f, 0.3f)));
		list[1] = new sphere(vec3(0.0f, -100.5f, -1.0f), 100.0f, new lambertian(vec3(0.8f, 0.8f, 0.0f)));
		list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8f, 0.6f, 0.2f)));
		list[3] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.8f, 0.8f, 0.8f)));

		hitable *world = new hitable_list(list, 4);

		camera cam;

		srand((unsigned)time(NULL));

		for (int j = ny - 1; j >= 0; j--)
		{
			for (int i = 0; i < nx; i++)
			{
				vec3 col(0.0f, 0.0f, 0.0f);

				for (int s = 0; s < ns; s++)
				{
					float rand1 = (rand() % 11) * 0.1f;
					float rand2 = (rand() % 11) * 0.1f;

					float u = float(i + rand1) / float(nx);
					float v = float(j + rand2) / float(ny);

					ray r = cam.get_ray(u, v);

					vec3 p = r.point_at_parameter(2.0f);
					col += color(r, world, 0);
				}

				col /= float(ns);
				col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

				int ir = int(255.99 * col[0]);
				int ig = int(255.99 * col[1]);
				int ib = int(255.99 * col[2]);

				writeFile << ir << " " << ig << " " << ib << "\n";
			}
		}
	}

	return 0;
}