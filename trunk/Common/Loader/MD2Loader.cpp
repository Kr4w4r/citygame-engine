#include "MD2Loader.h"

#include "stdio.h"

CMD2Loader::CMD2Loader()
{
	mSkins = NULL;
	mVertices = NULL;
}

CMD2Loader::~CMD2Loader()
{}

bool CMD2Loader::loadMD2(char* filePath)
{
	FILE* md2File = fopen(filePath, "r");

	if (md2File == NULL)
	{
		return false;
	}

	// MD2 Header auslesen
	T_MD2_HEADER md2Header;
	if (fread(&md2Header, sizeof(T_MD2_HEADER), 1, md2File) != 1)
	{
		// datei ist offenbar kleiner als der Header .. es kann also keine md2 sein
		return false;
	}

	// stimmt denn die Identnummer? IDP2 bzw. 844121161
	if ((md2Header.ident != 844121161) && (md2Header.version == 8))
	{
		return false;
	}

	if (md2Header.num_skins > 0)
	{
		mSkins = new T_MD2_SKIN[md2Header.num_skins];

		fread(mSkins, sizeof(T_MD2_SKIN), md2Header.num_skins, md2File);
	}

	// jetzt können wir alles erzeugen
	mVertices = new T_VEC3[md2Header.num_vertices];
	fread(mVertices, sizeof(T_VEC3), md2Header.num_vertices, md2File);

	fclose(md2File);
	return true;
}