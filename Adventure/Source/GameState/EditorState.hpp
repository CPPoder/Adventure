#ifndef EDITORSTATE_HPP
#define EDITORSTATE_HPP


#include "Source\GameState\GameState.hpp"
#include "Source\Game\GameBases\Editor.hpp"
#include "Source\ControlElements\Button.hpp"


namespace GameState
{

	class EditorState final : public GameState
	{
	private:
		Editor mEditor;

		sf::Vector2f mButtonSize = sf::Vector2f(20.f, 20.f);
		Button mExitButton;
		bool mCloseEditor = false;

	public:
		EditorState();
		virtual ~EditorState() override;

		virtual void update(sf::Time const & frametime, sf::RenderWindow* renderWindow) override;
		virtual void render(sf::RenderWindow* renderWindow) override;
		virtual GameStateChange pollGameStateChange() override;
		virtual void reactOnESC() override;


	};

}




#endif //EDITORSTATE_HPP

