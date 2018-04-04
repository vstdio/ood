#include "stdafx.h"
#include "Document.h"
#include "SetTitleCommand.h"
#include "InsertParagraphCommand.h"
#include "Menu.h"

using namespace std;
using namespace std::string_literals;

namespace
{
std::vector<std::string> Tokenize(std::istream& strm)
{
	std::vector<std::string> tokens;
	std::string token;
	while (strm >> token)
	{
		tokens.emplace_back(std::move(token));
	}
	return tokens;
}

class MenuCommandBinder
{
public:
	MenuCommandBinder(Menu& menu, Document& document)
		: m_menu(menu)
		, m_document(document)
	{
		using namespace std::placeholders;
		using std::bind;
		m_menu.AddItem("Exit", "Exit from menu", bind(&MenuCommandBinder::OnMenuExit, this, _1));
		m_menu.AddItem("Help", "Show menu instructions", bind(&MenuCommandBinder::OnMenuHelp, this, _1));
		m_menu.AddItem("SetTitle", "Set title to the document", bind(&MenuCommandBinder::OnDocumentSetTitle, this, _1));
		m_menu.AddItem("InsertParagraph", "Insert paragraph to the document", bind(&MenuCommandBinder::OnInsertParagraph, this, _1));
		m_menu.AddItem("List", "List all document's elements", bind(&MenuCommandBinder::OnList, this, _1));
		m_menu.AddItem("ReplaceText", "Replace text in paragraph at specified position", bind(&MenuCommandBinder::OnReplaceText, this, _1));
	}

private:
	void OnMenuExit(std::istream& strm)
	{
		(void)strm;
		m_menu.Exit();
	}

	void OnMenuHelp(std::istream& strm)
	{
		(void)strm;
		m_menu.ShowInstructions();
	}

	void OnDocumentSetTitle(std::istream& strm)
	{
		std::string title;
		if (strm >> title)
		{
			m_document.OnCommand(std::make_unique<SetTitleCommand>(title));
		}
		else
		{
			std::cout << "Please, provide title...\n";
		}
	}

	void OnInsertParagraph(std::istream& strm)
	{
		std::string token;
		auto args = Tokenize(strm);
		if (args.size() == 2u)
		{
			if (args[0] == "end"s)
			{
				m_document.OnCommand(make_unique<InsertParagraphCommand>(args[1]));
			}
			else
			{
				m_document.OnCommand(make_unique<InsertParagraphCommand>(args[1], stoul(args[0])));
			}
		}
		else
		{
			std::cout << "Please, provide position and text...\n";
		}
	}

	void OnList(std::istream& strm)
	{
		(void)strm;
		std::cout << "* Title: " << m_document.GetTitle() << std::endl;
		for (size_t i = 0; i < m_document.GetItemsCount(); ++i)
		{
			auto item = m_document.GetItem(i);
			auto pImage = item.GetImage();
			auto pParagraph = item.GetParagraph();
			if (pImage != nullptr)
			{
				assert(pParagraph == nullptr);
			}
			if (pParagraph != nullptr)
			{
				assert(pImage == nullptr);
			}
		}
	}

	void OnReplaceText(std::istream& strm)
	{
		const auto args = Tokenize(strm);
		if (args.size() != 2u)
		{
			std::cout << "Provide position and text" << std::endl;
			return;
		}
		const size_t pos = stoul(args[0]);
		if (pos >= m_document.GetItemsCount())
		{
			std::cout << "Invalid position specified" << std::endl;
		}
		auto docItem = m_document.GetItem(pos);
	}

	Menu& m_menu;
	Document& m_document;
};
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		Menu menu;
		Document document("hello"s);
		MenuCommandBinder binder(menu, document);
		menu.Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
