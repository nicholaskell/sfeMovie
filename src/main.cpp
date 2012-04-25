#include <SFML/Graphics.hpp>
#include <sfeMovie/Movie.hpp>

#ifndef MOVIE_FILE
#define MOVIE_FILE "bigBuck.ogg"
#endif

/*
 * Here is a little use sample for sfeMovie.
 * It'll open and display the movie specified by MOVIE_FILE above.
 *
 * This sample implements basic controls as follow:
 *  - Escape key to exit
 *  - Space key to play/pause the movie playback
 *  - S key to stop and go back to the beginning of the movie
 *  - R key to restart playing from the beginning of the movie
 *  - F key to toggle between windowed and fullscreen mode
 */

int main() {
	// Some settings
	const std::string windowTitle = "sfeMovie Player";
	const int windowWidth = 800;
	const int windowHeight = 600;
	bool fullscreen = false;

	// Create window
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
			windowTitle, sf::Style::Close);

	// Create and open movie
	sfe::Movie movie;
	if (!movie.openFromFile(MOVIE_FILE))
		return 1;

	// Scale movie to the window drawing area and enable VSync
	movie.resizeToFrame(0, 0, window.getSize().x, window.getSize().y);
	window.setVerticalSyncEnabled(true);

	// Start movie playback
	movie.play();

	movie.setOrigin(400.0, 250.0);
	movie.setPosition(400.0, 300.0);
	float rotation = 0.0;
	float scaleX = 0.5;
	float scaleY = 0.7;
	bool scaleXIncrease = false;
	bool scaleYIncrease = false;

	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			// Window closure
			if (ev.type == sf::Event::Closed
					|| (ev.type == sf::Event::KeyPressed
							&& ev.key.code == sf::Keyboard::Escape)) {
				window.close();
			}

			// Handle basic controls
			else if (ev.type == sf::Event::KeyPressed) {
				// Play/Pause
				if (ev.key.code == sf::Keyboard::Space) {
					if (movie.getStatus() != sfe::Movie::Playing)
						movie.play();
					else
						movie.pause();
				}

				// Stop
				if (ev.key.code == sf::Keyboard::S)
					movie.stop();

				// Restart playback
				if (ev.key.code == sf::Keyboard::R) {
					movie.stop();
					movie.play();
				}

				// Toggle fullscreen mode
				if (ev.key.code == sf::Keyboard::F) {
					fullscreen = !fullscreen;

					// We want to switch to the full screen mode
					if (fullscreen) {
						window.create(sf::VideoMode::getDesktopMode(),
								windowTitle, sf::Style::Fullscreen);
						window.setVerticalSyncEnabled(true);
						movie.resizeToFrame(0, 0, window.getSize().x,
								window.getSize().y);
					}

					// We want to switch back to the windowed mode
					else {
						window.create(sf::VideoMode(windowWidth, windowHeight),
								windowTitle, sf::Style::Close);
						window.setVerticalSyncEnabled(true);
						movie.resizeToFrame(0, 0, window.getSize().x,
								window.getSize().y);
					}
				}
			}
		}

		rotation += 0.2;

		if (scaleXIncrease) {
			scaleX += 0.02;
		} else {
			scaleX -= 0.004;
		}
		if (scaleX > 1.2) {
			scaleXIncrease = false;
		} else if (scaleX < 0.6) {
			scaleXIncrease = true;
		}

		if (scaleYIncrease) {
			scaleY += 0.009;
		} else {
			scaleY -= 0.005;
		}
		if (scaleY > 1.3) {
			scaleYIncrease = false;
		} else if (scaleY < 0.4) {
			scaleYIncrease = true;
		}

		movie.setRotation(rotation);
		movie.setScale(scaleX, scaleY);
		// Render movie
		window.clear();
		window.draw(movie);
		window.display();
	}

	return 0;
}

