#pragma once
class EnumToStringer
{
	SINGLE(EnumToStringer)

		inline wstring GetFruitName(FRUITS type) {
		switch (type)
		{
		case FRUITS::WATERMELON:
			return L"WATERMELON";
			break;
		case FRUITS::STARFRUIT:
			return L"STARFRUIT";
			break;
		case FRUITS::STRAWBERRY:
			return L"STRAWBERRY";
		case FRUITS::LEMON:
			return L"LEMON";
		case FRUITS::ORANGE:
			return L"ORANGE";
		case FRUITS::RASPBERRY:
			return L"RASPBERRY";
		case FRUITS::REDAPPLE:
			return L"REDAPPLE";
		case FRUITS::ROTTENFRUIT:
			return L"ROTTENFRUIT";
		}
	}
};

