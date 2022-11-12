// Alexander (AgitoReiKen) Moskalenko (C) 2022
#pragma once

#include "CoreMinimal.h"
#include "ColorUtils.generated.h"

USTRUCT()
struct FColorHSL
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0", ClampMax = "360", Units = "Degrees"), Category = "ColorHSL")
	/* Hue 0-360 */
	float H;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", Units = "Percent"), Category = "ColorHSL")
	/* Saturation 0-1 */
	float S;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", Units = "Percent"), Category = "ColorHSL")
	/* Luminocity 0-1 */
	float L;
	UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0", ClampMax = "1.0", Units = "Percent"), Category = "ColorHSL")
	/* Opacity 0-1 */
	float A;

	FColorHSL(float h = 0.0f, float s = 1.0f, float l = 1.0f, float a = 1.0f)
		: H(h),
		  S(s),
		  L(l),
		  A(a)
	{
	}

	FColorHSL(const FLinearColor& InColor)
	{
		const auto& val = FromRGB(InColor);
		H = val.H;
		S = val.S;
		L = val.L;
		A = val.A;
	}

	/* https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion */
	FLinearColor ToRGB() const
	{
		float r, g, b;
		if (S == 0.f)
			r = g = b = L;
		else
		{
			float q = L < 0.5f ? L * (1.0f + S) : L + S - L * S;
			float p = 2.0f * L - q;
			auto HueToRgb = [&p, &q](float t) -> float
			{
				if (t < 0.0f) t += 1.0f;
				if (t > 1.0f) t -= 1.0f;
				if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
				if (t < 1.0f / 2.0f) return q;
				if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
				return p;
			};
			float HueClamped = H / 360.f;
			r = HueToRgb(HueClamped + 1.0f / 3.0f);
			g = HueToRgb(HueClamped);
			b = HueToRgb(HueClamped - 1.0f / 3.0f);
		}
		return FLinearColor(r, g, b, A);
	}

	/* https://stackoverflow.com/questions/2353211/hsl-to-rgb-color-conversion */
	FLinearColor ToRGBCorrected() const
	{
		constexpr static float Delta = 2.2f;
		auto x = ToRGB();
		return {
			FMath::Pow(x.R, Delta),
			FMath::Pow(x.G, Delta),
			FMath::Pow(x.B, Delta),
			x.A
		};
	}

	/* https://stackoverflow.com/questions/39118528/rgb-to-hsl-conversion?rq=1 */
	static FColorHSL FromRGB(const FLinearColor& ClampedColor)
	{
		float max = FMath::Max3(ClampedColor.R, ClampedColor.G, ClampedColor.B);
		float min = FMath::Min3(ClampedColor.R, ClampedColor.G, ClampedColor.B);
		float Hue, Sat, Lum = Hue = Sat = (max + min) / 2;

		if (FMath::IsNearlyEqual(min, max, 0.001f))
		{
			Hue = Sat = 0;
		}
		else
		{
			float c = max - min;
			Sat = Lum > 0.5f ? c / (2.f - max - min) : c / (max + min);
			if (FMath::IsNearlyEqual(max, ClampedColor.R, 0.001f))
			{
				Hue = (ClampedColor.G - ClampedColor.B) / c + (ClampedColor.G < ClampedColor.B ? 6 : 0);
			}
			else if (FMath::IsNearlyEqual(max, ClampedColor.G, 0.001f))
			{
				Hue = (ClampedColor.B - ClampedColor.R) / c + 2;
			}
			else if (FMath::IsNearlyEqual(max, ClampedColor.B, 0.001f))
			{
				Hue = (ClampedColor.R - ClampedColor.G) / c + 4;
			}
		}
		return FColorHSL(Hue * 60.f, Sat, Lum, ClampedColor.A);
	}
};

USTRUCT()
struct FColorOkLab
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ColorOkLab")
	float L;
	UPROPERTY(EditAnywhere, Category = "ColorOkLab")
	float A;
	UPROPERTY(EditAnywhere, Category = "ColorOkLab")
	float B;
	UPROPERTY(EditAnywhere, Category = "ColorOkLab")
	float Alpha;

	FColorOkLab()
	{
		L = 0;
		A = 0;
		B = 0;
		Alpha = 1.0;
	}

	FColorOkLab(float L, float A, float B, float Alpha = 1.0f)
		: L(L),
		  A(A),
		  B(B),
		  Alpha(Alpha)
	{
	}

	FColorOkLab(const FLinearColor& RGB)
	{
		double r = RGB.R;
		double g = RGB.G;
		double b = RGB.B;

		r = ((r > 0.04045) ? FMath::Pow((r + 0.055) / 1.055, 2.4) : (r / 12.92));
		g = ((g > 0.04045) ? FMath::Pow((g + 0.055) / 1.055, 2.4) : (g / 12.92));
		b = ((b > 0.04045) ? FMath::Pow((b + 0.055) / 1.055, 2.4) : (b / 12.92));

		double l = 0.4121656120 * r + 0.5362752080 * g + 0.0514575653 * b;
		double m = 0.2118591070 * r + 0.6807189584 * g + 0.1074065790 * b;
		double s = 0.0883097947 * r + 0.2818474174 * g + 0.6302613616 * b;


		l = FMath::Pow(l, 1.0 / 3.0);
		m = FMath::Pow(m, 1.0 / 3.0);
		s = FMath::Pow(s, 1.0 / 3.0);

		L = 0.2104542553 * l + 0.7936177850 * m - 0.0040720468 * s;
		A = 1.9779984951 * l - 2.4285922050 * m + 0.4505937099 * s;
		B = 0.0259040371 * l + 0.7827717662 * m - 0.8086757660 * s;
		Alpha = RGB.A;
	}

	FLinearColor ToRGB()
	{
		FLinearColor Result;
		double l = L + 0.3963377774 * A + 0.2158037573 * B;
		double m = L - 0.1055613458 * A - 0.0638541728 * B;
		double s = L - 0.0894841775 * A - 1.2914855480 * B;

		l = l * l * l;
		m = m * m * m;
		s = s * s * s;

		double r = 4.0767245293 * l - 3.3072168827 * m + 0.2307590544 * s;
		double g = -1.2681437731 * l + 2.6093323231 * m - 0.3411344290 * s;
		double b = -0.0041119885 * l - 0.7034763098 * m + 1.7068625689 * s;

		r = ((r > 0.0031308) ? (1.055 * FMath::Pow(r, 1 / 2.4) - 0.055) : (12.92 * r));
		g = ((g > 0.0031308) ? (1.055 * FMath::Pow(g, 1 / 2.4) - 0.055) : (12.92 * g));
		b = ((b > 0.0031308) ? (1.055 * FMath::Pow(b, 1 / 2.4) - 0.055) : (12.92 * b));

		r = r < 0.0 ? 0.0 : (r > 1.0 ? 1.0 : r);
		g = g < 0.0 ? 0.0 : (g > 1.0 ? 1.0 : g);
		b = b < 0.0 ? 0.0 : (b > 1.0 ? 1.0 : b);

		Result.R = r;
		Result.G = g;
		Result.B = b;
		Result.A = Alpha;
		return Result;
	}
};

USTRUCT()
struct FColorOkLch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "ColorOkLch")
	float L;
	UPROPERTY(EditAnywhere, Category = "ColorOkLch")
	float C;
	UPROPERTY(EditAnywhere, Category = "ColorOkLch")
	float H;
	UPROPERTY(EditAnywhere, Category = "ColorOkLch")
	float Alpha;

	FColorOkLch()
	{
		L = 0;
		C = 0;
		H = 0;
		Alpha = 1.0;
	}

	FColorOkLch(float L, float C, float H, float Alpha = 1.0f)
		: L(L),
		  C(C),
		  H(H),
		  Alpha(Alpha)
	{
	}

	FColorOkLch(const FLinearColor& RGB)
	{
		FColorOkLab lab(RGB);

		double l = lab.L;
		double c = FMath::Sqrt(lab.A * lab.A + lab.B * lab.B);
		double h = FMath::Atan2(lab.B, lab.B);

		h = h / PI * 180;
		if (h < 0)
		{
			h += 360;
		}
		else if (h >= 360)
		{
			h -= 360;
		}

		L = l;
		C = c;
		H = h;
		Alpha = RGB.A;
	}

	FLinearColor ToRGB()
	{
		double h = H * PI / 180;
		FColorOkLab lab(L, FMath::Cos(h) * C, FMath::Sin(h) * C, Alpha);
		return lab.ToRGB();
	}

	FLinearColor ToRGBCorrected()
	{
		static constexpr float Delta = 2.2f;
		FLinearColor Result = ToRGB();
		return {
			FMath::Pow(Result.R, Delta),
			FMath::Pow(Result.G, Delta),
			FMath::Pow(Result.B, Delta),
			Result.A
		};
	}
};
