#ifndef EDITORSTATE_HPP
#define EDITORSTATE_HPP


#include "Source\GameState\GameState.hpp"
#include "Source\Game\Editor.hpp"


namespace GameState
{

	class EditorState final : public GameState
	{
	private:
		Editor mEditor;

	public:
		EditorState();
		virtual ~EditorState() override;

		virtual void update(sf::Time const & frametime, sf::RenderWindow* renderWindow) override;
		virtual void render(sf::RenderWindow* renderWindow) override;
		virtual GameStateChange getGameStateChange() const override;


	};

}




#endif //EDITORSTATE_HPP

