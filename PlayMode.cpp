#include "PlayMode.hpp"

#include "LitColorTextureProgram.hpp"

#include "DrawLines.hpp"
#include "Mesh.hpp"
#include "Load.hpp"
#include "gl_errors.hpp"
#include "data_path.hpp"

#include <glm/gtc/type_ptr.hpp>

#include <random>

GLuint hexapod_meshes_for_lit_color_texture_program = 0;
Load< MeshBuffer > hexapod_meshes(LoadTagDefault, []() -> MeshBuffer const * {
	MeshBuffer const *ret = new MeshBuffer(data_path("swan_lake.pnct"));
	hexapod_meshes_for_lit_color_texture_program = ret->make_vao_for_program(lit_color_texture_program->program);
	return ret;
});

Load< Scene > hexapod_scene(LoadTagDefault, []() -> Scene const * {
	return new Scene(data_path("swan_lake.scene"), [&](Scene &scene, Scene::Transform *transform, std::string const &mesh_name){
		Mesh const &mesh = hexapod_meshes->lookup(mesh_name);

		scene.drawables.emplace_back(transform);
		Scene::Drawable &drawable = scene.drawables.back();

		drawable.pipeline = lit_color_texture_program_pipeline;

		drawable.pipeline.vao = hexapod_meshes_for_lit_color_texture_program;
		drawable.pipeline.type = mesh.type;
		drawable.pipeline.start = mesh.start;
		drawable.pipeline.count = mesh.count;

	});
});

Load< Sound::Sample > swan_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("swan.opus"));
});

Load< Sound::Sample > wind_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("swan.opus"));
});

Load< Sound::Sample > win_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("swan.opus"));
});

Load< Sound::Sample > lose_sample(LoadTagDefault, []() -> Sound::Sample const * {
	return new Sound::Sample(data_path("swan.opus"));
});

PlayMode::PlayMode() : scene(*hexapod_scene) {
	//https://en.cppreference.com/w/cpp/numeric/random/rand#:~:text=If%20rand()%20is%20used,of%20values%20on%20successive%20calls.
	std::srand(std::time(nullptr)); 

	for (auto &transform : scene.transforms) {
		if (transform.name == "Duck") duck = &transform;
		else if (transform.name == "UpT") upT = &transform;
		else if (transform.name == "DownT") downT = &transform;
		else if (transform.name == "LeftT") leftT = &transform;
		else if (transform.name == "RightT") rightT = &transform;
		else if (transform.name == "Down.001") down1 = &transform;
		else if (transform.name == "Down.002") down2 = &transform;
		else if (transform.name == "Down.003") down3 = &transform;
		else if (transform.name == "Down.004") down4 = &transform;
		else if (transform.name == "Down.005") down5 = &transform;
		else if (transform.name == "Down.006") down6 = &transform;
		else if (transform.name == "Up.001") up1 = &transform;
		else if (transform.name == "Up.002") up2 = &transform;
		else if (transform.name == "Up.003") up3 = &transform;
		else if (transform.name == "Up.004") up4 = &transform;
		else if (transform.name == "Up.005") up5 = &transform;
		else if (transform.name == "Up.006") up6 = &transform;
		else if (transform.name == "Left.001") left1 = &transform;
		else if (transform.name == "Left.002") left2 = &transform;
		else if (transform.name == "Left.003") left3 = &transform;
		else if (transform.name == "Left.004") left4 = &transform;
		else if (transform.name == "Left.005") left5 = &transform;
		else if (transform.name == "Left.006") left6 = &transform;
		else if (transform.name == "Right.001") right1 = &transform;
		else if (transform.name == "Right.002") right2 = &transform;
		else if (transform.name == "Right.003") right3 = &transform;
		else if (transform.name == "Right.004") right4 = &transform;
		else if (transform.name == "Right.005") right5 = &transform;
		else if (transform.name == "Right.006") right6 = &transform;
		
	}
	if (duck == nullptr) throw std::runtime_error("Duck not found.");
	else if (upT == nullptr) throw std::runtime_error("upT not found.");
	else if (downT == nullptr) throw std::runtime_error("downT not found.");
	else if (leftT == nullptr) throw std::runtime_error("leftT not found.");
	else if (rightT == nullptr) throw std::runtime_error("rightT not found.");
	else if (down1 == nullptr) throw std::runtime_error("down1 not found.");
	else if (down2 == nullptr) throw std::runtime_error("down2 not found.");
	else if (down3 == nullptr) throw std::runtime_error("down3 not found.");
	else if (down4 == nullptr) throw std::runtime_error("down4 not found.");
	else if (down5 == nullptr) throw std::runtime_error("down5 not found.");
	else if (down6 == nullptr) throw std::runtime_error("down6 not found.");
	else if (up1 == nullptr) throw std::runtime_error("up1 not found.");
	else if (up2 == nullptr) throw std::runtime_error("up2 not found.");
	else if (up3 == nullptr) throw std::runtime_error("up3 not found.");
	else if (up4 == nullptr) throw std::runtime_error("up4 not found.");
	else if (up5 == nullptr) throw std::runtime_error("up5 not found.");
	else if (up6 == nullptr) throw std::runtime_error("up6 not found.");
	else if (left1 == nullptr) throw std::runtime_error("left1 not found.");
	else if (left2 == nullptr) throw std::runtime_error("left2 not found.");
	else if (left3 == nullptr) throw std::runtime_error("left3 not found.");
	else if (left4 == nullptr) throw std::runtime_error("left4 not found.");
	else if (left5 == nullptr) throw std::runtime_error("left5 not found.");
	else if (left6 == nullptr) throw std::runtime_error("left6 not found.");
	else if (right1 == nullptr) throw std::runtime_error("right1 not found.");
	else if (right2 == nullptr) throw std::runtime_error("right2 not found.");
	else if (right3 == nullptr) throw std::runtime_error("right3 not found.");
	else if (right4 == nullptr) throw std::runtime_error("right4 not found.");
	else if (right5 == nullptr) throw std::runtime_error("right5 not found.");
	else if (right6 == nullptr) throw std::runtime_error("right6 not found.");

	arrow_bbox = glm::vec2(0.1f,0.1f);

	up_bbox_min = upT->position - arrow_bbox;
	up_bbox_max = upT->position + arrow_bbox;

	down_bbox_min = downT->position - arrow_bbox;
	down_bbox_max = downT->position + arrow_bbox;

	left_bbox_min = leftT->position - arrow_bbox;
	left_bbox_max = leftT->position + arrow_bbox;

	right_bbox_min = rightT->position - arrow_bbox;
	right_bbox_max = rightT->position + arrow_bbox;

	duck_rotation = duck->rotation;

	arrows[0].arrow = down1;
	arrows[1].arrow = down2;
	arrows[2].arrow = down3;
	arrows[3].arrow = down4;
	arrows[4].arrow = down5;
	arrows[5].arrow = down6;
	arrows[6].arrow = up1;
	arrows[7].arrow = up2;
	arrows[8].arrow = up3;
	arrows[9].arrow = up4;
	arrows[10].arrow = up5;
	arrows[11].arrow = up6;
	arrows[12].arrow = left1;
	arrows[13].arrow = left2;
	arrows[14].arrow = left3;
	arrows[15].arrow = left4;
	arrows[16].arrow = left5;
	arrows[17].arrow = left6;
	arrows[18].arrow = right1;
	arrows[19].arrow = right2;
	arrows[20].arrow = right3;
	arrows[21].arrow = right4;
	arrows[22].arrow = right5;
	arrows[23].arrow = right6;

	for(uint32_t i = 0; i < 24; i++){
		order[i] = std::rand()
	}

	//get pointer to camera for convenience:
	if (scene.cameras.size() != 1) throw std::runtime_error("Expecting scene to have exactly one camera, but it has " + std::to_string(scene.cameras.size()));
	camera = &scene.cameras.front();

	//start music loop playing:
	// (note: position will be over-ridden in update())
	wind_loop = Sound::loop_3D(*swan_sample, 1.0f, get_duck_position(), 10.0f);
}

PlayMode::~PlayMode() {
}

bool PlayMode::handle_event(SDL_Event const &evt, glm::uvec2 const &window_size) {

	if (evt.type == SDL_KEYDOWN) {
		if (evt.key.keysym.sym == SDLK_ESCAPE) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			left.downs += 1;
			left.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_LEFT) {
			right.downs += 1;
			right.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.downs += 1;
			up.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.downs += 1;
			down.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			a.downs += 1;
			a.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			d.downs += 1;
			d.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			w.downs += 1;
			w.pressed = true;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			s.downs += 1;
			s.pressed = true;
			return true;
		}
	} else if (evt.type == SDL_KEYUP) {
		if (evt.key.keysym.sym == SDLK_LEFT) {
			left.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_RIGHT) {
			right.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_UP) {
			up.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_DOWN) {
			down.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_a) {
			a.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_d) {
			d.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_w) {
			w.pressed = false;
			return true;
		} else if (evt.key.keysym.sym == SDLK_s) {
			s.pressed = false;
			return true;
		}
	}

	return false;
}

void PlayMode::update(float elapsed) {

	//slowly rotates through [0,1):
	wobble += elapsed / 10.0f;
	wobble -= std::floor(wobble);

	wind_loop->set_position(get_duck_position(), 1.0f / 60.0f);

	{
		//Make inputs move around duck
		float PlayerSpeed = 30.0f;
		glm::vec2 move = glm::vec2(0.0f);
		if (a.pressed && !d.pressed) {
			move.y = 1.0f;
			duck->rotation = duck_rotation * glm::angleAxis(glm::radians(-90.f),glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (!a.pressed && d.pressed) {
			move.y = -1.0f;
			duck->rotation = duck_rotation * glm::angleAxis(glm::radians(90.f),glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (s.pressed && !w.pressed) {
			move.x = -1.0f;
			duck->rotation = duck_rotation * glm::angleAxis(glm::radians(0.f),glm::vec3(0.0f, 0.0f, 1.0f));
		}
		if (!s.pressed && w.pressed) {
			move.x = 1.0f;
			duck->rotation = duck_rotation * glm::angleAxis(glm::radians(180.f),glm::vec3(0.0f, 0.0f, 1.0f));
		}

		//make it so that moving diagonally doesn't go faster:
		if (move != glm::vec2(0.0f)) move = glm::normalize(move) * PlayerSpeed * elapsed;

		glm::mat4x3 frame = duck->make_local_to_parent();
		glm::vec3 frame_right = frame[0] * duck->rotation;
		glm::vec3 up = frame[1] * duck->rotation;

		duck->position += move.x * frame_right + move.y * up;

		// clamp to within grassy area
		duck->position.x = std::clamp(duck->position.x, 1.f, 8.f);
		duck->position.y = std::clamp(duck->position.y, -3.f, 3.f);

		
		// hard coded bbox for podium :(
		if ((abs(duck->position.x-2.4f) < 0.6f) && (1.5f - abs(duck->position.y) > 0.f)){
			duck->position.x = (duck->position.x < 2.4f) ? 1.8f : 3.f;
		}
		if((1.5f - abs(duck->position.y) > 0.f) && (1.5f - abs(duck->position.y) < 1.f)){
			if(abs(duck->position.x-5.5f) < 0.7f) {
				duck->position.x = (duck->position.x < 5.5f) ? 4.8f : 6.2f;
			}
		}

		if(abs(duck->position.x - 4.f) < 2.f) {
			if(abs(duck->position.y - 1.5f) < 0.5f){
				duck->position.y = (duck->position.y < 1.5f) ? 1.f : 2.f;
			} else if (abs(duck->position.y + 1.5f) < 0.5f) {
				duck->position.y = (duck->position.y < -1.5) ? -2.f : -1.f;
			}
		}
	}

	{ //update listener to camera position:
		glm::mat4x3 frame = camera->transform->make_local_to_parent();
		glm::vec3 frame_right = frame[0];
		glm::vec3 frame_at = frame[3];
		Sound::listener.set_position_right(frame_at, frame_right, 1.0f / 60.0f);
	}

	{ // update arrow locations + detect podium
		if(!on_podium && abs(duck->position.x - 4.f) < 1.f && abs(duck->position.y) < 1.5f){
			on_podium = true;
		} else {
			on_podium = false;
			timer = start_rate;
		}
		
		if(on_podium){
			timer = std::max(timer - elapsed, 0.f);
			if(timer <= 0.f) {
				// start song
				swan_song = Sound::play(*swan_sample, 1.0f, 10.0f);
			}
		}

		float ArrowSpeed = 40.0f;
	}

	{ // check for arrow collisions
		// https://developer.mozilla.org/en-US/docs/Games/Techniques/3D_collision_detection
		if (left.pressed && !right.pressed) {
			glm::vec2 rmin = left_bbox_min;
			glm::vec2 rmax = left_bbox_max;

			for(uint32_t i = 12; i < 18; i++){
				glm::vec2 mmin = arrows[i].arrow->position - arrow_bbox;
				glm::vec2 mmax = arrows[i].arrow->position + arrow_bbox;
				if (mmin.x <= rmax.x && mmax.x >= rmin.x && mmin.y <= rmax.y && mmax.y >= rmin.y && arrows[i].on_screen){
					arrows[i].on_screen = false;
					arrows[i].arrow->position.x = 5.5f;
					arrows[i].arrow->position.y = leftT->position.y;
				}
			}
		}
		if (!left.pressed && right.pressed) {
			glm::vec2 rmin = right_bbox_min;
			glm::vec2 rmax = right_bbox_max;

			for(uint32_t i = 18; i < 24; i++){
				glm::vec2 mmin = arrows[i].arrow->position - arrow_bbox;
				glm::vec2 mmax = arrows[i].arrow->position + arrow_bbox;
				if (mmin.x <= rmax.x && mmax.x >= rmin.x && mmin.y <= rmax.y && mmax.y >= rmin.y && arrows[i].on_screen){
					arrows[i].on_screen = false;
					arrows[i].arrow->position.x = 5.5f;
					arrows[i].arrow->position.y = rightT->position.y;
				}
			}
		}
		if (down.pressed && !up.pressed) {
			glm::vec2 rmin = down_bbox_min;
			glm::vec2 rmax = down_bbox_max;

			for(uint32_t i = 0; i < 6; i++){
				glm::vec2 mmin = arrows[i].arrow->position - arrow_bbox;
				glm::vec2 mmax = arrows[i].arrow->position + arrow_bbox;
				if (mmin.x <= rmax.x && mmax.x >= rmin.x && mmin.y <= rmax.y && mmax.y >= rmin.y && arrows[i].on_screen){
					arrows[i].on_screen = false;
					arrows[i].arrow->position.x = 5.5f;
					arrows[i].arrow->position.y = downT->position.y;
				}
			}
		}
		if (!down.pressed && up.pressed) {
			glm::vec2 rmin = up_bbox_min;
			glm::vec2 rmax = up_bbox_max;

			for(uint32_t i = 0; i < 6; i++){
				glm::vec2 mmin = arrows[i].arrow->position - arrow_bbox;
				glm::vec2 mmax = arrows[i].arrow->position + arrow_bbox;
				if (mmin.x <= rmax.x && mmax.x >= rmin.x && mmin.y <= rmax.y && mmax.y >= rmin.y && arrows[i].on_screen){
					arrows[i].on_screen = false;
					arrows[i].arrow->position.x = 5.5f;
					arrows[i].arrow->position.y = upT->position.y;
				}
			}
		}
	}

	//reset button press counters:
	left.downs = 0;
	right.downs = 0;
	up.downs = 0;
	down.downs = 0;

	w.downs = 0;
	a.downs = 0;
	s.downs = 0;
	d.downs = 0;
}

void PlayMode::draw(glm::uvec2 const &drawable_size) {
	//update camera aspect ratio for drawable:
	camera->aspect = float(drawable_size.x) / float(drawable_size.y);

	//set up light type and position for lit_color_texture_program:
	// TODO: consider using the Light(s) in the scene to do this
	glUseProgram(lit_color_texture_program->program);
	glUniform1i(lit_color_texture_program->LIGHT_TYPE_int, 1);
	glUniform3fv(lit_color_texture_program->LIGHT_DIRECTION_vec3, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f,-1.0f)));
	glUniform3fv(lit_color_texture_program->LIGHT_ENERGY_vec3, 1, glm::value_ptr(glm::vec3(0.4f, 0.4f, 0.95f)));
	glUseProgram(0);

	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClearDepth(1.0f); //1.0 is actually the default value to clear the depth buffer to, but FYI you can change it.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); //this is the default depth comparison function, but FYI you can change it.

	scene.draw(*camera);

	{ //use DrawLines to overlay some text:
		glDisable(GL_DEPTH_TEST);
		float aspect = float(drawable_size.x) / float(drawable_size.y);
		DrawLines lines(glm::mat4(
			1.0f / aspect, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		));

		constexpr float H = 0.09f;
		lines.draw_text("WASD moves",
			glm::vec3(-aspect + 0.1f * H, -1.0 + 0.1f * H, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0x00, 0x00, 0x00, 0x00));
		float ofs = 2.0f / drawable_size.y;
		lines.draw_text("WASD moves",
			glm::vec3(-aspect + 0.1f * H + ofs, -1.0 + + 0.1f * H + ofs, 0.0),
			glm::vec3(H, 0.0f, 0.0f), glm::vec3(0.0f, H, 0.0f),
			glm::u8vec4(0xff, 0xff, 0xff, 0x00));
	}
	GL_ERRORS();
}

glm::vec3 PlayMode::get_duck_position() {
	//the vertex position here was read from the model in blender:
	return duck->make_local_to_world() * glm::vec4(-1.26137f, -11.861f, 0.0f, 1.0f);
}
