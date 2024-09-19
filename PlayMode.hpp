#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>
#include <queue>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up, w, a, s, d;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	Scene::Transform *duck = nullptr;
	Scene::Transform *upT = nullptr;
	Scene::Transform *downT = nullptr;
	Scene::Transform *leftT = nullptr;
	Scene::Transform *rightT = nullptr;

	Scene::Transform *up1 = nullptr;
	Scene::Transform *up2 = nullptr;
	Scene::Transform *up3 = nullptr;
	Scene::Transform *up4 = nullptr;
	Scene::Transform *up5 = nullptr;
	Scene::Transform *up6 = nullptr;

	Scene::Transform *down1 = nullptr;
	Scene::Transform *down2 = nullptr;
	Scene::Transform *down3 = nullptr;
	Scene::Transform *down4 = nullptr;
	Scene::Transform *down5 = nullptr;
	Scene::Transform *down6 = nullptr;

	Scene::Transform *left1 = nullptr;
	Scene::Transform *left2 = nullptr;
	Scene::Transform *left3 = nullptr;
	Scene::Transform *left4 = nullptr;
	Scene::Transform *left5 = nullptr;
	Scene::Transform *left6 = nullptr;

	Scene::Transform *right1 = nullptr;
	Scene::Transform *right2 = nullptr;
	Scene::Transform *right3 = nullptr;
	Scene::Transform *right4 = nullptr;
	Scene::Transform *right5 = nullptr;
	Scene::Transform *right6 = nullptr;

	glm::vec2 up_bbox_minmax;
	glm::vec2 down_bbox_minmax;
	glm::vec2 left_bbox_minmax;
	glm::vec2 right_bbox_minmax;

	float arrow_threshold = 0.6f;

	glm::quat duck_rotation;
	
	const float start_rate = 3.f;
	const float arrow_rate = 1.f;
	const float off_screen_x = 20.5f;

	float timer = start_rate;
	float arrow_timer = arrow_rate;
	bool started = false;
	bool on_podium = false;

	struct Arrow {
		Scene::Transform *arrow = nullptr;
		bool on_screen = false;
	};

	Arrow arrows[24];

	std::deque<uint32_t> arrow_order;

	int score = 0;

	glm::vec3 get_duck_position();

	std::shared_ptr< Sound::PlayingSample > swan_song;
	std::shared_ptr< Sound::PlayingSample > wind_loop;
	
	//camera:
	Scene::Camera *camera = nullptr;

};
