#ifndef GAME_H
#define GAME_H
#define USE_SDL_TTF
#include"Goat2d/Scene.h"
#include<list>
#include<random>
#include"Matrix.hpp"
using namespace Goat2d::core;

typedef pair<Color, size_t> block;
typedef variant<block, void*> el;

constexpr const auto DIFF = 123 / 4;//use it to compute text positions

class Game :public Goat2d::framework::BaseScene
{
	std::list<Goat2d::core::Rectangle*> background;
	Matrix<el>* field = nullptr;

	Color** colors = nullptr;
	const size_t COLORS_NUMBER = 3;

	int complexity_level;
	Font *font, *small_font; 
	int high_score = 0;
public:
	Game(int id, 
		 SDL_Renderer* renderer, 
		 std::unordered_map<int, Font*>& fonts,
		 int complexity_level);
	~Game();

	void render() override;
private:
	void init_background();
	void init_colors();
	void init_field();

	void generate_random_block();


	Vector2i get_random_pos();
	std::vector<Vector2i> get_empty_cells();

	int get_random_number(int a, int b);
	inline Color get_random_color();

	
	void draw_blocks();

	void iterate_over_matrix_4_times(const std::function<void(const Vector2i& pos)>& fn);
	void move_element(const Vector2i& pos, const Vector2i& dir, bool move_down=false);

	void create_left_movement_event();
	void create_right_movement_event();
	void create_up_movement_event();
	void create_down_movement_event();
	void create_check_losing_event();

	int get_high_score();

	Vector2i compute_text_pos(const Vector2i& pos);

};

#endif