// Copyright Reality Engine. All Rights Reserved.

#pragma once

namespace reality::primitiveHelper {
	constexpr float g_Quad[]{ -0.5f,0.5f,0.f,0.f,0.f,-1.f,0.f,1.f,0.5f,0.5f,0.f,0.f,0.f,-1.f,1.f,1.f,-0.5f,-0.5f,0.f,0.f,0.f,-1.f,0.f,0.f,0.5f,0.5f,0.f,0.f,0.f,-1.f,1.f,1.f,0.5f,-0.5f,0.f,0.f,0.f,-1.f,1.f,0.f,-0.5f,-0.5f,0.f,0.f,0.f,-1.f,0.f,0.f };
	constexpr float g_Cube[]{ 0.5f,-0.5f,-0.5f,0.f,0.f,-1.f,1.f,0.f,-0.5f,-0.5f,-0.5f,0.f,0.f,-1.f,0.f,0.f,0.5f,0.5f,-0.5f,0.f,0.f,-1.f,1.f,1.f,0.5f,0.5f,-0.5f,0.f,0.f,-1.f,1.f,1.f,-0.5f,-0.5f,-0.5f,0.f,0.f,-1.f,0.f,0.f,-0.5f,0.5f,-0.5f,0.f,0.f,-1.f,0.f,1.f,-0.5f,-0.5f,0.5f,0.f,0.f,1.f,0.f,0.f,0.5f,-0.5f,0.5f,0.f,0.f,1.f,1.f,0.f,0.5f,0.5f,0.5f,0.f,0.f,1.f,1.f,1.f,0.5f,0.5f,0.5f,0.f,0.f,1.f,1.f,1.f,-0.5f,0.5f,0.5f,0.f,0.f,1.f,0.f,1.f,-0.5f,-0.5f,0.5f,0.f,0.f,1.f,0.f,0.f,-0.5f,0.5f,0.5f,-1.f,0.f,0.f,1.f,0.f,-0.5f,0.5f,-0.5f,-1.f,0.f,0.f,1.f,1.f,-0.5f,-0.5f,-0.5f,-1.f,0.f,0.f,0.f,1.f,-0.5f,-0.5f,-0.5f,-1.f,0.f,0.f,0.f,1.f,-0.5f,-0.5f,0.5f,-1.f,0.f,0.f,0.f,0.f,-0.5f,0.5f,0.5f,-1.f,0.f,0.f,1.f,0.f,0.5f,0.5f,-0.5f,1.f,0.f,0.f,1.f,1.f,0.5f,0.5f,0.5f,1.f,0.f,0.f,1.f,0.f,0.5f,-0.5f,-0.5f,1.f,0.f,0.f,0.f,1.f,0.5f,-0.5f,-0.5f,1.f,0.f,0.f,0.f,1.f,0.5f,0.5f,0.5f,1.f,0.f,0.f,1.f,0.f,0.5f,-0.5f,0.5f,1.f,0.f,0.f,0.f,0.f,-0.5f,-0.5f,-0.5f,0.f,-1.f,0.f,0.f,1.f,0.5f,-0.5f,-0.5f,0.f,-1.f,0.f,1.f,1.f,0.5f,-0.5f,0.5f,0.f,-1.f,0.f,1.f,0.f,0.5f,-0.5f,0.5f,0.f,-1.f,0.f,1.f,0.f,-0.5f,-0.5f,0.5f,0.f,-1.f,0.f,0.f,0.f,-0.5f,-0.5f,-0.5f,0.f,-1.f,0.f,0.f,1.f,0.5f,0.5f,-0.5f,0.f,1.f,0.f,1.f,1.f,-0.5f,0.5f,-0.5f,0.f,1.f,0.f,0.f,1.f,0.5f,0.5f,0.5f,0.f,1.f,0.f,1.f,0.f,-0.5f,0.5f,0.5f,0.f,1.f,0.f,0.f,0.f,0.5f,0.5f,0.5f,0.f,1.f,0.f,1.f,0.f,-0.5f,0.5f,-0.5f,0.f,1.f,0.f,0.f,1.f };
	constexpr float g_Circle[]{ 0.5f,0.f,0.f,0.499013f,0.0313953f,0.f,0.496057f,0.0626666f,0.f,0.491144f,0.0936907f,0.f,0.484292f,0.124345f,0.f,0.475528f,0.154509f,0.f,0.464888f,0.184062f,0.f,0.452414f,0.21289f,0.f,0.438153f,0.240877f,0.f,0.422164f,0.267913f,0.f,0.404509f,0.293893f,0.f,0.385257f,0.318712f,0.f,0.364484f,0.342274f,0.f,0.342274f,0.364484f,0.f,0.318712f,0.385257f,0.f,0.293893f,0.404509f,0.f,0.267913f,0.422164f,0.f,0.240877f,0.438153f,0.f,0.21289f,0.452414f,0.f,0.184062f,0.464888f,0.f,0.154508f,0.475528f,0.f,0.124345f,0.484292f,0.f,0.0936906f,0.491144f,0.f,0.0626666f,0.496057f,0.f,0.0313952f,0.499013f,0.f,-2.18557e-08f,0.5f,0.f,-0.0313953f,0.499013f,0.f,-0.0626667f,0.496057f,0.f,-0.0936907f,0.491144f,0.f,-0.124345f,0.484292f,0.f,-0.154509f,0.475528f,0.f,-0.184062f,0.464888f,0.f,-0.21289f,0.452413f,0.f,-0.240877f,0.438153f,0.f,-0.267913f,0.422164f,0.f,-0.293893f,0.404508f,0.f,-0.318712f,0.385257f,0.f,-0.342274f,0.364484f,0.f,-0.364484f,0.342274f,0.f,-0.385257f,0.318712f,0.f,-0.404509f,0.293893f,0.f,-0.422164f,0.267913f,0.f,-0.438153f,0.240877f,0.f,-0.452414f,0.21289f,0.f,-0.464888f,0.184062f,0.f,-0.475528f,0.154508f,0.f,-0.484292f,0.124345f,0.f,-0.491144f,0.0936905f,0.f,-0.496057f,0.0626666f,0.f,-0.499013f,0.0313951f,0.f,-0.5f,-4.37114e-08f,0.f,-0.499013f,-0.0313954f,0.f,-0.496057f,-0.0626667f,0.f,-0.491144f,-0.0936906f,0.f,-0.484292f,-0.124345f,0.f,-0.475528f,-0.154508f,0.f,-0.464888f,-0.184062f,0.f,-0.452414f,-0.21289f,0.f,-0.438153f,-0.240877f,0.f,-0.422164f,-0.267913f,0.f,-0.404508f,-0.293893f,0.f,-0.385257f,-0.318712f,0.f,-0.364484f,-0.342274f,0.f,-0.342273f,-0.364484f,0.f,-0.318712f,-0.385257f,0.f,-0.293893f,-0.404508f,0.f,-0.267913f,-0.422164f,0.f,-0.240877f,-0.438153f,0.f,-0.21289f,-0.452414f,0.f,-0.184062f,-0.464888f,0.f,-0.154508f,-0.475528f,0.f,-0.124345f,-0.484292f,0.f,-0.0936907f,-0.491144f,0.f,-0.0626666f,-0.496057f,0.f,-0.0313953f,-0.499013f,0.f,5.96244e-09f,-0.5f,0.f,0.0313953f,-0.499013f,0.f,0.0626666f,-0.496057f,0.f,0.0936907f,-0.491144f,0.f,0.124345f,-0.484292f,0.f,0.154509f,-0.475528f,0.f,0.184062f,-0.464888f,0.f,0.21289f,-0.452413f,0.f,0.240877f,-0.438153f,0.f,0.267913f,-0.422164f,0.f,0.293893f,-0.404509f,0.f,0.318712f,-0.385257f,0.f,0.342274f,-0.364484f,0.f,0.364484f,-0.342273f,0.f,0.385257f,-0.318712f,0.f,0.404509f,-0.293892f,0.f,0.422164f,-0.267913f,0.f,0.438153f,-0.240877f,0.f,0.452414f,-0.21289f,0.f,0.464888f,-0.184062f,0.f,0.475528f,-0.154508f,0.f,0.484292f,-0.124345f,0.f,0.491144f,-0.0936906f,0.f,0.496057f,-0.0626663f,0.f,0.499013f,-0.0313952f,0.f };
	constexpr float g_SphereVertices[]{ -2.18557e-08f,-0.f,0.5f,-2.0786e-08f,-6.75378e-09f,0.5f,-1.76816e-08f,-1.28465e-08f,0.5f,-1.28465e-08f,-1.76816e-08f,0.5f,-6.75378e-09f,-2.0786e-08f,0.5f,9.55343e-16f,-2.18557e-08f,0.5f,6.75378e-09f,-2.0786e-08f,0.5f,1.28465e-08f,-1.76816e-08f,0.5f,1.76816e-08f,-1.28465e-08f,0.5f,2.0786e-08f,-6.75378e-09f,0.5f,2.18557e-08f,1.91069e-15f,0.5f,2.0786e-08f,6.75378e-09f,0.5f,1.76816e-08f,1.28465e-08f,0.5f,1.28465e-08f,1.76816e-08f,0.5f,6.75378e-09f,2.0786e-08f,0.5f,-2.60627e-16f,2.18557e-08f,0.5f,-6.75378e-09f,2.0786e-08f,0.5f,-1.28465e-08f,1.76816e-08f,0.5f,-1.76816e-08f,1.28464e-08f,0.5f,-2.0786e-08f,6.75378e-09f,0.5f,-2.18557e-08f,-3.82137e-15f,0.5f,0.0782172f,0.f,0.493844f,0.074389f,0.0241704f,0.493844f,0.063279f,0.0459749f,0.493844f,0.0459749f,0.063279f,0.493844f,0.0241704f,0.074389f,0.493844f,-3.41898e-09f,0.0782172f,0.493844f,-0.0241704f,0.074389f,0.493844f,-0.0459749f,0.063279f,0.493844f,-0.063279f,0.0459749f,0.493844f,-0.074389f,0.0241704f,0.493844f,-0.0782172f,-6.83796e-09f,0.493844f,-0.074389f,-0.0241704f,0.493844f,-0.063279f,-0.0459749f,0.493844f,-0.0459749f,-0.063279f,0.493844f,-0.0241704f,-0.074389f,0.493844f,9.32731e-10f,-0.0782172f,0.493844f,0.0241704f,-0.074389f,0.493844f,0.0459749f,-0.063279f,0.493844f,0.0632791f,-0.0459749f,0.493844f,0.074389f,-0.0241704f,0.493844f,0.0782172f,1.36759e-08f,0.493844f,0.154508f,0.f,0.475528f,0.146946f,0.0477457f,0.475528f,0.125f,0.0908178f,0.475528f,0.0908178f,0.125f,0.475528f,0.0477457f,0.146946f,0.475528f,-6.75378e-09f,0.154508f,0.475528f,-0.0477458f,0.146946f,0.475528f,-0.0908178f,0.125f,0.475528f,-0.125f,0.0908178f,0.475528f,-0.146946f,0.0477457f,0.475528f,-0.154508f,-1.35076e-08f,0.475528f,-0.146946f,-0.0477457f,0.475528f,-0.125f,-0.0908178f,0.475528f,-0.0908178f,-0.125f,0.475528f,-0.0477458f,-0.146946f,0.475528f,1.8425e-09f,-0.154508f,0.475528f,0.0477458f,-0.146946f,0.475528f,0.0908178f,-0.125f,0.475528f,0.125f,-0.0908178f,0.475528f,0.146946f,-0.0477457f,0.475528f,0.154508f,2.70151e-08f,0.475528f,0.226995f,0.f,0.445503f,0.215885f,0.0701454f,0.445503f,0.183643f,0.133424f,0.445503f,0.133424f,0.183643f,0.445503f,0.0701454f,0.215885f,0.445503f,-9.92228e-09f,0.226995f,0.445503f,-0.0701454f,0.215885f,0.445503f,-0.133424f,0.183643f,0.445503f,-0.183643f,0.133424f,0.445503f,-0.215885f,0.0701453f,0.445503f,-0.226995f,-1.98446e-08f,0.445503f,-0.215885f,-0.0701454f,0.445503f,-0.183643f,-0.133424f,0.445503f,-0.133424f,-0.183643f,0.445503f,-0.0701454f,-0.215885f,0.445503f,2.70689e-09f,-0.226995f,0.445503f,0.0701454f,-0.215885f,0.445503f,0.133425f,-0.183643f,0.445503f,0.183643f,-0.133424f,0.445503f,0.215885f,-0.0701454f,0.445503f,0.226995f,3.96891e-08f,0.445503f,0.293893f,0.f,0.404509f,0.279509f,0.0908178f,0.404509f,0.237764f,0.172746f,0.404509f,0.172746f,0.237764f,0.404509f,0.0908178f,0.279509f,0.404509f,-1.28465e-08f,0.293893f,0.404509f,-0.0908178f,0.279508f,0.404509f,-0.172746f,0.237764f,0.404509f,-0.237764f,0.172746f,0.404509f,-0.279509f,0.0908178f,0.404509f,-0.293893f,-2.56929e-08f,0.404509f,-0.279509f,-0.0908178f,0.404509f,-0.237764f,-0.172746f,0.404509f,-0.172746f,-0.237764f,0.404509f,-0.0908178f,-0.279508f,0.404509f,3.50463e-09f,-0.293893f,0.404509f,0.0908179f,-0.279508f,0.404509f,0.172746f,-0.237764f,0.404509f,0.237764f,-0.172746f,0.404509f,0.279509f,-0.0908178f,0.404509f,0.293893f,5.13858e-08f,0.404509f,0.353553f,0.f,0.353553f,0.336249f,0.109254f,0.353553f,0.286031f,0.207813f,0.353553f,0.207813f,0.286031f,0.353553f,0.109254f,0.336249f,0.353553f,-1.54543e-08f,0.353553f,0.353553f,-0.109254f,0.336249f,0.353553f,-0.207813f,0.286031f,0.353553f,-0.286031f,0.207813f,0.353553f,-0.336249f,0.109254f,0.353553f,-0.353553f,-3.09086e-08f,0.353553f,-0.336249f,-0.109254f,0.353553f,-0.286031f,-0.207814f,0.353553f,-0.207813f,-0.286031f,0.353553f,-0.109254f,-0.336249f,0.353553f,4.21608e-09f,-0.353553f,0.353553f,0.109254f,-0.336249f,0.353553f,0.207814f,-0.286031f,0.353553f,0.286031f,-0.207813f,0.353553f,0.336249f,-0.109254f,0.353553f,0.353553f,6.18172e-08f,0.353553f,0.404509f,0.f,0.293893f,0.38471f,0.125f,0.293893f,0.327254f,0.237764f,0.293893f,0.237764f,0.327254f,0.293893f,0.125f,0.38471f,0.293893f,-1.76816e-08f,0.404509f,0.293893f,-0.125f,0.38471f,0.293893f,-0.237764f,0.327254f,0.293893f,-0.327254f,0.237764f,0.293893f,-0.38471f,0.125f,0.293893f,-0.404509f,-3.53633e-08f,0.293893f,-0.38471f,-0.125f,0.293893f,-0.327254f,-0.237764f,0.293893f,-0.237764f,-0.327254f,0.293893f,-0.125f,-0.38471f,0.293893f,4.82372e-09f,-0.404509f,0.293893f,0.125f,-0.38471f,0.293893f,0.237764f,-0.327254f,0.293893f,0.327254f,-0.237764f,0.293893f,0.38471f,-0.125f,0.293893f,0.404509f,7.07265e-08f,0.293893f,0.445503f,0.f,0.226995f,0.423699f,0.137668f,0.226995f,0.36042f,0.26186f,0.226995f,0.26186f,0.36042f,0.226995f,0.137668f,0.423699f,0.226995f,-1.94736e-08f,0.445503f,0.226995f,-0.137668f,0.423699f,0.226995f,-0.26186f,0.36042f,0.226995f,-0.36042f,0.26186f,0.226995f,-0.423699f,0.137668f,0.226995f,-0.445503f,-3.89471e-08f,0.226995f,-0.423699f,-0.137668f,0.226995f,-0.36042f,-0.26186f,0.226995f,-0.26186f,-0.36042f,0.226995f,-0.137668f,-0.423699f,0.226995f,5.31257e-09f,-0.445503f,0.226995f,0.137668f,-0.423699f,0.226995f,0.26186f,-0.36042f,0.226995f,0.36042f,-0.26186f,0.226995f,0.423699f,-0.137668f,0.226995f,0.445503f,7.78943e-08f,0.226995f,0.475528f,0.f,0.154509f,0.452254f,0.146946f,0.154509f,0.38471f,0.279509f,0.154509f,0.279509f,0.38471f,0.154509f,0.146946f,0.452254f,0.154509f,-2.0786e-08f,0.475528f,0.154509f,-0.146946f,0.452254f,0.154509f,-0.279508f,0.38471f,0.154509f,-0.38471f,0.279508f,0.154509f,-0.452254f,0.146946f,0.154509f,-0.475528f,-4.1572e-08f,0.154509f,-0.452254f,-0.146946f,0.154509f,-0.38471f,-0.279509f,0.154509f,-0.279508f,-0.384711f,0.154509f,-0.146946f,-0.452254f,0.154509f,5.67062e-09f,-0.475528f,0.154509f,0.146946f,-0.452254f,0.154509f,0.279509f,-0.38471f,0.154509f,0.384711f,-0.279508f,0.154509f,0.452254f,-0.146946f,0.154509f,0.475528f,8.3144e-08f,0.154509f,0.493844f,0.f,0.0782172f,0.469674f,0.152606f,0.0782172f,0.399528f,0.290274f,0.0782172f,0.290274f,0.399528f,0.0782172f,0.152606f,0.469674f,0.0782172f,-2.15866e-08f,0.493844f,0.0782172f,-0.152606f,0.469674f,0.0782172f,-0.290274f,0.399528f,0.0782172f,-0.399528f,0.290274f,0.0782172f,-0.469674f,0.152606f,0.0782172f,-0.493844f,-4.31732e-08f,0.0782172f,-0.469674f,-0.152606f,0.0782172f,-0.399528f,-0.290274f,0.0782172f,-0.290274f,-0.399528f,0.0782172f,-0.152606f,-0.469674f,0.0782172f,5.88903e-09f,-0.493844f,0.0782172f,0.152606f,-0.469674f,0.0782172f,0.290274f,-0.399528f,0.0782172f,0.399528f,-0.290274f,0.0782172f,0.469674f,-0.152606f,0.0782172f,0.493844f,8.63465e-08f,0.0782172f,0.5f,0.f,0.f,0.475528f,0.154509f,0.f,0.404509f,0.293893f,0.f,0.293893f,0.404509f,0.f,0.154508f,0.475528f,0.f,-2.18557e-08f,0.5f,0.f,-0.154509f,0.475528f,0.f,-0.293893f,0.404509f,0.f,-0.404509f,0.293893f,0.f,-0.475528f,0.154508f,0.f,-0.5f,-4.37114e-08f,0.f,-0.475528f,-0.154508f,0.f,-0.404508f,-0.293893f,0.f,-0.293893f,-0.404509f,0.f,-0.154509f,-0.475528f,0.f,5.96244e-09f,-0.5f,0.f,0.154509f,-0.475528f,0.f,0.293893f,-0.404508f,0.f,0.404509f,-0.293892f,0.f,0.475528f,-0.154508f,0.f,0.5f,8.74228e-08f,0.f,0.493844f,0.f,-0.0782172f,0.469674f,0.152606f,-0.0782172f,0.399528f,0.290274f,-0.0782172f,0.290274f,0.399528f,-0.0782172f,0.152606f,0.469674f,-0.0782172f,-2.15866e-08f,0.493844f,-0.0782172f,-0.152606f,0.469674f,-0.0782172f,-0.290274f,0.399528f,-0.0782172f,-0.399528f,0.290274f,-0.0782172f,-0.469674f,0.152606f,-0.0782172f,-0.493844f,-4.31732e-08f,-0.0782172f,-0.469674f,-0.152606f,-0.0782172f,-0.399528f,-0.290274f,-0.0782172f,-0.290274f,-0.399528f,-0.0782172f,-0.152606f,-0.469674f,-0.0782172f,5.88903e-09f,-0.493844f,-0.0782172f,0.152606f,-0.469674f,-0.0782172f,0.290274f,-0.399528f,-0.0782172f,0.399528f,-0.290274f,-0.0782172f,0.469674f,-0.152606f,-0.0782172f,0.493844f,8.63465e-08f,-0.0782172f,0.475528f,0.f,-0.154509f,0.452254f,0.146946f,-0.154509f,0.38471f,0.279509f,-0.154509f,0.279509f,0.38471f,-0.154509f,0.146946f,0.452254f,-0.154509f,-2.0786e-08f,0.475528f,-0.154509f,-0.146946f,0.452254f,-0.154509f,-0.279508f,0.38471f,-0.154509f,-0.38471f,0.279508f,-0.154509f,-0.452254f,0.146946f,-0.154509f,-0.475528f,-4.1572e-08f,-0.154509f,-0.452254f,-0.146946f,-0.154509f,-0.38471f,-0.279509f,-0.154509f,-0.279508f,-0.384711f,-0.154509f,-0.146946f,-0.452254f,-0.154509f,5.67062e-09f,-0.475528f,-0.154509f,0.146946f,-0.452254f,-0.154509f,0.279509f,-0.38471f,-0.154509f,0.384711f,-0.279508f,-0.154509f,0.452254f,-0.146946f,-0.154509f,0.475528f,8.3144e-08f,-0.154509f,0.445503f,0.f,-0.226995f,0.423699f,0.137668f,-0.226995f,0.36042f,0.26186f,-0.226995f,0.26186f,0.36042f,-0.226995f,0.137668f,0.423699f,-0.226995f,-1.94736e-08f,0.445503f,-0.226995f,-0.137668f,0.423699f,-0.226995f,-0.26186f,0.36042f,-0.226995f,-0.36042f,0.26186f,-0.226995f,-0.423699f,0.137668f,-0.226995f,-0.445503f,-3.89471e-08f,-0.226995f,-0.423699f,-0.137668f,-0.226995f,-0.36042f,-0.26186f,-0.226995f,-0.26186f,-0.36042f,-0.226995f,-0.137668f,-0.423699f,-0.226995f,5.31257e-09f,-0.445503f,-0.226995f,0.137668f,-0.423699f,-0.226995f,0.26186f,-0.36042f,-0.226995f,0.36042f,-0.26186f,-0.226995f,0.423699f,-0.137668f,-0.226995f,0.445503f,7.78943e-08f,-0.226995f,0.404509f,0.f,-0.293893f,0.38471f,0.125f,-0.293893f,0.327254f,0.237764f,-0.293893f,0.237764f,0.327254f,-0.293893f,0.125f,0.38471f,-0.293893f,-1.76816e-08f,0.404509f,-0.293893f,-0.125f,0.38471f,-0.293893f,-0.237764f,0.327254f,-0.293893f,-0.327254f,0.237764f,-0.293893f,-0.384711f,0.125f,-0.293893f,-0.404509f,-3.53633e-08f,-0.293893f,-0.38471f,-0.125f,-0.293893f,-0.327254f,-0.237764f,-0.293893f,-0.237764f,-0.327254f,-0.293893f,-0.125f,-0.38471f,-0.293893f,4.82372e-09f,-0.404509f,-0.293893f,0.125f,-0.38471f,-0.293893f,0.237764f,-0.327254f,-0.293893f,0.327254f,-0.237764f,-0.293893f,0.38471f,-0.125f,-0.293893f,0.404509f,7.07265e-08f,-0.293893f,0.353553f,0.f,-0.353553f,0.336249f,0.109254f,-0.353553f,0.286031f,0.207813f,-0.353553f,0.207813f,0.286031f,-0.353553f,0.109254f,0.336249f,-0.353553f,-1.54543e-08f,0.353553f,-0.353553f,-0.109254f,0.336249f,-0.353553f,-0.207813f,0.286031f,-0.353553f,-0.286031f,0.207813f,-0.353553f,-0.336249f,0.109254f,-0.353553f,-0.353553f,-3.09086e-08f,-0.353553f,-0.336249f,-0.109254f,-0.353553f,-0.286031f,-0.207814f,-0.353553f,-0.207813f,-0.286031f,-0.353553f,-0.109254f,-0.336249f,-0.353553f,4.21608e-09f,-0.353553f,-0.353553f,0.109254f,-0.336249f,-0.353553f,0.207814f,-0.286031f,-0.353553f,0.286031f,-0.207813f,-0.353553f,0.336249f,-0.109254f,-0.353553f,0.353553f,6.18172e-08f,-0.353553f,0.293893f,0.f,-0.404509f,0.279509f,0.0908178f,-0.404509f,0.237764f,0.172746f,-0.404509f,0.172746f,0.237764f,-0.404509f,0.0908178f,0.279509f,-0.404509f,-1.28465e-08f,0.293893f,-0.404509f,-0.0908178f,0.279508f,-0.404509f,-0.172746f,0.237764f,-0.404509f,-0.237764f,0.172746f,-0.404509f,-0.279509f,0.0908178f,-0.404509f,-0.293893f,-2.56929e-08f,-0.404509f,-0.279509f,-0.0908178f,-0.404509f,-0.237764f,-0.172746f,-0.404509f,-0.172746f,-0.237764f,-0.404509f,-0.0908178f,-0.279508f,-0.404509f,3.50463e-09f,-0.293893f,-0.404509f,0.0908179f,-0.279508f,-0.404509f,0.172746f,-0.237764f,-0.404509f,0.237764f,-0.172746f,-0.404509f,0.279509f,-0.0908178f,-0.404509f,0.293893f,5.13858e-08f,-0.404509f,0.226995f,0.f,-0.445503f,0.215885f,0.0701454f,-0.445503f,0.183643f,0.133424f,-0.445503f,0.133424f,0.183643f,-0.445503f,0.0701454f,0.215885f,-0.445503f,-9.92228e-09f,0.226995f,-0.445503f,-0.0701454f,0.215885f,-0.445503f,-0.133424f,0.183643f,-0.445503f,-0.183643f,0.133424f,-0.445503f,-0.215885f,0.0701453f,-0.445503f,-0.226995f,-1.98446e-08f,-0.445503f,-0.215885f,-0.0701454f,-0.445503f,-0.183643f,-0.133424f,-0.445503f,-0.133424f,-0.183643f,-0.445503f,-0.0701454f,-0.215885f,-0.445503f,2.70689e-09f,-0.226995f,-0.445503f,0.0701454f,-0.215885f,-0.445503f,0.133424f,-0.183643f,-0.445503f,0.183643f,-0.133424f,-0.445503f,0.215885f,-0.0701454f,-0.445503f,0.226995f,3.96891e-08f,-0.445503f,0.154508f,0.f,-0.475528f,0.146946f,0.0477457f,-0.475528f,0.125f,0.0908178f,-0.475528f,0.0908178f,0.125f,-0.475528f,0.0477457f,0.146946f,-0.475528f,-6.75378e-09f,0.154508f,-0.475528f,-0.0477457f,0.146946f,-0.475528f,-0.0908178f,0.125f,-0.475528f,-0.125f,0.0908178f,-0.475528f,-0.146946f,0.0477457f,-0.475528f,-0.154508f,-1.35076e-08f,-0.475528f,-0.146946f,-0.0477457f,-0.475528f,-0.125f,-0.0908178f,-0.475528f,-0.0908177f,-0.125f,-0.475528f,-0.0477457f,-0.146946f,-0.475528f,1.84249e-09f,-0.154508f,-0.475528f,0.0477457f,-0.146946f,-0.475528f,0.0908178f,-0.125f,-0.475528f,0.125f,-0.0908177f,-0.475528f,0.146946f,-0.0477457f,-0.475528f,0.154508f,2.70151e-08f,-0.475528f,0.0782172f,0.f,-0.493844f,0.074389f,0.0241705f,-0.493844f,0.0632791f,0.0459749f,-0.493844f,0.0459749f,0.0632791f,-0.493844f,0.0241705f,0.074389f,-0.493844f,-3.41898e-09f,0.0782172f,-0.493844f,-0.0241705f,0.074389f,-0.493844f,-0.0459749f,0.0632791f,-0.493844f,-0.0632791f,0.0459749f,-0.493844f,-0.074389f,0.0241704f,-0.493844f,-0.0782172f,-6.83797e-09f,-0.493844f,-0.074389f,-0.0241705f,-0.493844f,-0.0632791f,-0.045975f,-0.493844f,-0.0459749f,-0.0632791f,-0.493844f,-0.0241705f,-0.074389f,-0.493844f,9.32731e-10f,-0.0782172f,-0.493844f,0.0241705f,-0.074389f,-0.493844f,0.045975f,-0.0632791f,-0.493844f,0.0632791f,-0.0459749f,-0.493844f,0.074389f,-0.0241705f,-0.493844f,0.0782172f,1.36759e-08f,-0.493844f,-2.18557e-08f,-0.f,-0.5f,-2.0786e-08f,-6.75378e-09f,-0.5f,-1.76816e-08f,-1.28465e-08f,-0.5f,-1.28465e-08f,-1.76816e-08f,-0.5f,-6.75378e-09f,-2.0786e-08f,-0.5f,9.55343e-16f,-2.18557e-08f,-0.5f,6.75378e-09f,-2.0786e-08f,-0.5f,1.28465e-08f,-1.76816e-08f,-0.5f,1.76816e-08f,-1.28465e-08f,-0.5f,2.0786e-08f,-6.75378e-09f,-0.5f,2.18557e-08f,1.91069e-15f,-0.5f,2.0786e-08f,6.75378e-09f,-0.5f,1.76816e-08f,1.28465e-08f,-0.5f,1.28465e-08f,1.76816e-08f,-0.5f,6.75378e-09f,2.0786e-08f,-0.5f,-2.60627e-16f,2.18557e-08f,-0.5f,-6.75378e-09f,2.0786e-08f,-0.5f,-1.28465e-08f,1.76816e-08f,-0.5f,-1.76816e-08f,1.28464e-08f,-0.5f,-2.0786e-08f,6.75378e-09f,-0.5f,-2.18557e-08f,-3.82137e-15f,-0.5f };
	constexpr unsigned g_SphereIndices[]{ 1u,21u,22u,2u,22u,23u,3u,23u,24u,4u,24u,25u,5u,25u,26u,6u,26u,27u,7u,27u,28u,8u,28u,29u,9u,29u,30u,10u,30u,31u,11u,31u,32u,12u,32u,33u,13u,33u,34u,14u,34u,35u,15u,35u,36u,16u,36u,37u,17u,37u,38u,18u,38u,39u,19u,39u,40u,20u,40u,41u,21u,42u,22u,22u,42u,43u,22u,43u,23u,23u,43u,44u,23u,44u,24u,24u,44u,45u,24u,45u,25u,25u,45u,46u,25u,46u,26u,26u,46u,47u,26u,47u,27u,27u,47u,48u,27u,48u,28u,28u,48u,49u,28u,49u,29u,29u,49u,50u,29u,50u,30u,30u,50u,51u,30u,51u,31u,31u,51u,52u,31u,52u,32u,32u,52u,53u,32u,53u,33u,33u,53u,54u,33u,54u,34u,34u,54u,55u,34u,55u,35u,35u,55u,56u,35u,56u,36u,36u,56u,57u,36u,57u,37u,37u,57u,58u,37u,58u,38u,38u,58u,59u,38u,59u,39u,39u,59u,60u,39u,60u,40u,40u,60u,61u,40u,61u,41u,41u,61u,62u,42u,63u,43u,43u,63u,64u,43u,64u,44u,44u,64u,65u,44u,65u,45u,45u,65u,66u,45u,66u,46u,46u,66u,67u,46u,67u,47u,47u,67u,68u,47u,68u,48u,48u,68u,69u,48u,69u,49u,49u,69u,70u,49u,70u,50u,50u,70u,71u,50u,71u,51u,51u,71u,72u,51u,72u,52u,52u,72u,73u,52u,73u,53u,53u,73u,74u,53u,74u,54u,54u,74u,75u,54u,75u,55u,55u,75u,76u,55u,76u,56u,56u,76u,77u,56u,77u,57u,57u,77u,78u,57u,78u,58u,58u,78u,79u,58u,79u,59u,59u,79u,80u,59u,80u,60u,60u,80u,81u,60u,81u,61u,61u,81u,82u,61u,82u,62u,62u,82u,83u,63u,84u,64u,64u,84u,85u,64u,85u,65u,65u,85u,86u,65u,86u,66u,66u,86u,87u,66u,87u,67u,67u,87u,88u,67u,88u,68u,68u,88u,89u,68u,89u,69u,69u,89u,90u,69u,90u,70u,70u,90u,91u,70u,91u,71u,71u,91u,92u,71u,92u,72u,72u,92u,93u,72u,93u,73u,73u,93u,94u,73u,94u,74u,74u,94u,95u,74u,95u,75u,75u,95u,96u,75u,96u,76u,76u,96u,97u,76u,97u,77u,77u,97u,98u,77u,98u,78u,78u,98u,99u,78u,99u,79u,79u,99u,100u,79u,100u,80u,80u,100u,101u,80u,101u,81u,81u,101u,102u,81u,102u,82u,82u,102u,103u,82u,103u,83u,83u,103u,104u,84u,105u,85u,85u,105u,106u,85u,106u,86u,86u,106u,107u,86u,107u,87u,87u,107u,108u,87u,108u,88u,88u,108u,109u,88u,109u,89u,89u,109u,110u,89u,110u,90u,90u,110u,111u,90u,111u,91u,91u,111u,112u,91u,112u,92u,92u,112u,113u,92u,113u,93u,93u,113u,114u,93u,114u,94u,94u,114u,115u,94u,115u,95u,95u,115u,116u,95u,116u,96u,96u,116u,117u,96u,117u,97u,97u,117u,118u,97u,118u,98u,98u,118u,119u,98u,119u,99u,99u,119u,120u,99u,120u,100u,100u,120u,121u,100u,121u,101u,101u,121u,122u,101u,122u,102u,102u,122u,123u,102u,123u,103u,103u,123u,124u,103u,124u,104u,104u,124u,125u,105u,126u,106u,106u,126u,127u,106u,127u,107u,107u,127u,128u,107u,128u,108u,108u,128u,129u,108u,129u,109u,109u,129u,130u,109u,130u,110u,110u,130u,131u,110u,131u,111u,111u,131u,132u,111u,132u,112u,112u,132u,133u,112u,133u,113u,113u,133u,134u,113u,134u,114u,114u,134u,135u,114u,135u,115u,115u,135u,136u,115u,136u,116u,116u,136u,137u,116u,137u,117u,117u,137u,138u,117u,138u,118u,118u,138u,139u,118u,139u,119u,119u,139u,140u,119u,140u,120u,120u,140u,141u,120u,141u,121u,121u,141u,142u,121u,142u,122u,122u,142u,143u,122u,143u,123u,123u,143u,144u,123u,144u,124u,124u,144u,145u,124u,145u,125u,125u,145u,146u,126u,147u,127u,127u,147u,148u,127u,148u,128u,128u,148u,149u,128u,149u,129u,129u,149u,150u,129u,150u,130u,130u,150u,151u,130u,151u,131u,131u,151u,152u,131u,152u,132u,132u,152u,153u,132u,153u,133u,133u,153u,154u,133u,154u,134u,134u,154u,155u,134u,155u,135u,135u,155u,156u,135u,156u,136u,136u,156u,157u,136u,157u,137u,137u,157u,158u,137u,158u,138u,138u,158u,159u,138u,159u,139u,139u,159u,160u,139u,160u,140u,140u,160u,161u,140u,161u,141u,141u,161u,162u,141u,162u,142u,142u,162u,163u,142u,163u,143u,143u,163u,164u,143u,164u,144u,144u,164u,165u,144u,165u,145u,145u,165u,166u,145u,166u,146u,146u,166u,167u,147u,168u,148u,148u,168u,169u,148u,169u,149u,149u,169u,170u,149u,170u,150u,150u,170u,171u,150u,171u,151u,151u,171u,172u,151u,172u,152u,152u,172u,173u,152u,173u,153u,153u,173u,174u,153u,174u,154u,154u,174u,175u,154u,175u,155u,155u,175u,176u,155u,176u,156u,156u,176u,177u,156u,177u,157u,157u,177u,178u,157u,178u,158u,158u,178u,179u,158u,179u,159u,159u,179u,180u,159u,180u,160u,160u,180u,181u,160u,181u,161u,161u,181u,182u,161u,182u,162u,162u,182u,183u,162u,183u,163u,163u,183u,184u,163u,184u,164u,164u,184u,185u,164u,185u,165u,165u,185u,186u,165u,186u,166u,166u,186u,187u,166u,187u,167u,167u,187u,188u,168u,189u,169u,169u,189u,190u,169u,190u,170u,170u,190u,191u,170u,191u,171u,171u,191u,192u,171u,192u,172u,172u,192u,193u,172u,193u,173u,173u,193u,194u,173u,194u,174u,174u,194u,195u,174u,195u,175u,175u,195u,196u,175u,196u,176u,176u,196u,197u,176u,197u,177u,177u,197u,198u,177u,198u,178u,178u,198u,199u,178u,199u,179u,179u,199u,200u,179u,200u,180u,180u,200u,201u,180u,201u,181u,181u,201u,202u,181u,202u,182u,182u,202u,203u,182u,203u,183u,183u,203u,204u,183u,204u,184u,184u,204u,205u,184u,205u,185u,185u,205u,206u,185u,206u,186u,186u,206u,207u,186u,207u,187u,187u,207u,208u,187u,208u,188u,188u,208u,209u,189u,210u,190u,190u,210u,211u,190u,211u,191u,191u,211u,212u,191u,212u,192u,192u,212u,213u,192u,213u,193u,193u,213u,214u,193u,214u,194u,194u,214u,215u,194u,215u,195u,195u,215u,216u,195u,216u,196u,196u,216u,217u,196u,217u,197u,197u,217u,218u,197u,218u,198u,198u,218u,219u,198u,219u,199u,199u,219u,220u,199u,220u,200u,200u,220u,221u,200u,221u,201u,201u,221u,222u,201u,222u,202u,202u,222u,223u,202u,223u,203u,203u,223u,224u,203u,224u,204u,204u,224u,225u,204u,225u,205u,205u,225u,226u,205u,226u,206u,206u,226u,227u,206u,227u,207u,207u,227u,228u,207u,228u,208u,208u,228u,229u,208u,229u,209u,209u,229u,230u,210u,231u,211u,211u,231u,232u,211u,232u,212u,212u,232u,233u,212u,233u,213u,213u,233u,234u,213u,234u,214u,214u,234u,235u,214u,235u,215u,215u,235u,236u,215u,236u,216u,216u,236u,237u,216u,237u,217u,217u,237u,238u,217u,238u,218u,218u,238u,239u,218u,239u,219u,219u,239u,240u,219u,240u,220u,220u,240u,241u,220u,241u,221u,221u,241u,242u,221u,242u,222u,222u,242u,243u,222u,243u,223u,223u,243u,244u,223u,244u,224u,224u,244u,245u,224u,245u,225u,225u,245u,246u,225u,246u,226u,226u,246u,247u,226u,247u,227u,227u,247u,248u,227u,248u,228u,228u,248u,249u,228u,249u,229u,229u,249u,250u,229u,250u,230u,230u,250u,251u,231u,252u,232u,232u,252u,253u,232u,253u,233u,233u,253u,254u,233u,254u,234u,234u,254u,255u,234u,255u,235u,235u,255u,256u,235u,256u,236u,236u,256u,257u,236u,257u,237u,237u,257u,258u,237u,258u,238u,238u,258u,259u,238u,259u,239u,239u,259u,260u,239u,260u,240u,240u,260u,261u,240u,261u,241u,241u,261u,262u,241u,262u,242u,242u,262u,263u,242u,263u,243u,243u,263u,264u,243u,264u,244u,244u,264u,265u,244u,265u,245u,245u,265u,266u,245u,266u,246u,246u,266u,267u,246u,267u,247u,247u,267u,268u,247u,268u,248u,248u,268u,269u,248u,269u,249u,249u,269u,270u,249u,270u,250u,250u,270u,271u,250u,271u,251u,251u,271u,272u,252u,273u,253u,253u,273u,274u,253u,274u,254u,254u,274u,275u,254u,275u,255u,255u,275u,276u,255u,276u,256u,256u,276u,277u,256u,277u,257u,257u,277u,278u,257u,278u,258u,258u,278u,279u,258u,279u,259u,259u,279u,280u,259u,280u,260u,260u,280u,281u,260u,281u,261u,261u,281u,282u,261u,282u,262u,262u,282u,283u,262u,283u,263u,263u,283u,284u,263u,284u,264u,264u,284u,285u,264u,285u,265u,265u,285u,286u,265u,286u,266u,266u,286u,287u,266u,287u,267u,267u,287u,288u,267u,288u,268u,268u,288u,289u,268u,289u,269u,269u,289u,290u,269u,290u,270u,270u,290u,291u,270u,291u,271u,271u,291u,292u,271u,292u,272u,272u,292u,293u,273u,294u,274u,274u,294u,295u,274u,295u,275u,275u,295u,296u,275u,296u,276u,276u,296u,297u,276u,297u,277u,277u,297u,298u,277u,298u,278u,278u,298u,299u,278u,299u,279u,279u,299u,300u,279u,300u,280u,280u,300u,301u,280u,301u,281u,281u,301u,302u,281u,302u,282u,282u,302u,303u,282u,303u,283u,283u,303u,304u,283u,304u,284u,284u,304u,305u,284u,305u,285u,285u,305u,306u,285u,306u,286u,286u,306u,307u,286u,307u,287u,287u,307u,308u,287u,308u,288u,288u,308u,309u,288u,309u,289u,289u,309u,310u,289u,310u,290u,290u,310u,311u,290u,311u,291u,291u,311u,312u,291u,312u,292u,292u,312u,313u,292u,313u,293u,293u,313u,314u,294u,315u,295u,295u,315u,316u,295u,316u,296u,296u,316u,317u,296u,317u,297u,297u,317u,318u,297u,318u,298u,298u,318u,319u,298u,319u,299u,299u,319u,320u,299u,320u,300u,300u,320u,321u,300u,321u,301u,301u,321u,322u,301u,322u,302u,302u,322u,323u,302u,323u,303u,303u,323u,324u,303u,324u,304u,304u,324u,325u,304u,325u,305u,305u,325u,326u,305u,326u,306u,306u,326u,327u,306u,327u,307u,307u,327u,328u,307u,328u,308u,308u,328u,329u,308u,329u,309u,309u,329u,330u,309u,330u,310u,310u,330u,331u,310u,331u,311u,311u,331u,332u,311u,332u,312u,312u,332u,333u,312u,333u,313u,313u,333u,334u,313u,334u,314u,314u,334u,335u,315u,336u,316u,316u,336u,337u,316u,337u,317u,317u,337u,338u,317u,338u,318u,318u,338u,339u,318u,339u,319u,319u,339u,340u,319u,340u,320u,320u,340u,341u,320u,341u,321u,321u,341u,342u,321u,342u,322u,322u,342u,343u,322u,343u,323u,323u,343u,344u,323u,344u,324u,324u,344u,345u,324u,345u,325u,325u,345u,346u,325u,346u,326u,326u,346u,347u,326u,347u,327u,327u,347u,348u,327u,348u,328u,328u,348u,349u,328u,349u,329u,329u,349u,350u,329u,350u,330u,330u,350u,351u,330u,351u,331u,331u,351u,352u,331u,352u,332u,332u,352u,353u,332u,353u,333u,333u,353u,354u,333u,354u,334u,334u,354u,355u,334u,355u,335u,335u,355u,356u,336u,357u,337u,337u,357u,358u,337u,358u,338u,338u,358u,359u,338u,359u,339u,339u,359u,360u,339u,360u,340u,340u,360u,361u,340u,361u,341u,341u,361u,362u,341u,362u,342u,342u,362u,363u,342u,363u,343u,343u,363u,364u,343u,364u,344u,344u,364u,365u,344u,365u,345u,345u,365u,366u,345u,366u,346u,346u,366u,367u,346u,367u,347u,347u,367u,368u,347u,368u,348u,348u,368u,369u,348u,369u,349u,349u,369u,370u,349u,370u,350u,350u,370u,371u,350u,371u,351u,351u,371u,372u,351u,372u,352u,352u,372u,373u,352u,373u,353u,353u,373u,374u,353u,374u,354u,354u,374u,375u,354u,375u,355u,355u,375u,376u,355u,376u,356u,356u,376u,377u,357u,378u,358u,358u,378u,379u,358u,379u,359u,359u,379u,380u,359u,380u,360u,360u,380u,381u,360u,381u,361u,361u,381u,382u,361u,382u,362u,362u,382u,383u,362u,383u,363u,363u,383u,384u,363u,384u,364u,364u,384u,385u,364u,385u,365u,365u,385u,386u,365u,386u,366u,366u,386u,387u,366u,387u,367u,367u,387u,388u,367u,388u,368u,368u,388u,389u,368u,389u,369u,369u,389u,390u,369u,390u,370u,370u,390u,391u,370u,391u,371u,371u,391u,392u,371u,392u,372u,372u,392u,393u,372u,393u,373u,373u,393u,394u,373u,394u,374u,374u,394u,395u,374u,395u,375u,375u,395u,396u,375u,396u,376u,376u,396u,397u,376u,397u,377u,377u,397u,398u,378u,399u,379u,379u,399u,400u,379u,400u,380u,380u,400u,401u,380u,401u,381u,381u,401u,402u,381u,402u,382u,382u,402u,403u,382u,403u,383u,383u,403u,404u,383u,404u,384u,384u,404u,405u,384u,405u,385u,385u,405u,406u,385u,406u,386u,386u,406u,407u,386u,407u,387u,387u,407u,408u,387u,408u,388u,388u,408u,409u,388u,409u,389u,389u,409u,410u,389u,410u,390u,390u,410u,411u,390u,411u,391u,391u,411u,412u,391u,412u,392u,392u,412u,413u,392u,413u,393u,393u,413u,414u,393u,414u,394u,394u,414u,415u,394u,415u,395u,395u,415u,416u,395u,416u,396u,396u,416u,417u,396u,417u,397u,397u,417u,418u,397u,418u,398u,398u,418u,419u,399u,420u,400u,400u,421u,401u,401u,422u,402u,402u,423u,403u,403u,424u,404u,404u,425u,405u,405u,426u,406u,406u,427u,407u,407u,428u,408u,408u,429u,409u,409u,430u,410u,410u,431u,411u,411u,432u,412u,412u,433u,413u,413u,434u,414u,414u,435u,415u,415u,436u,416u,416u,437u,417u,417u,438u,418u,418u,439u,419u };
}