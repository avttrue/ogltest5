uniform sampler2D u_texture;
uniform highp vec4 u_lightPosition;
uniform highp float u_lightPower; // сила освещения
varying highp vec4 v_position;
varying highp vec2 v_textcoord;
varying highp vec3 v_normal;

void main(void)
{
    vec4 resultColor = vec4(0.0, 0.0, 0.0, 0.0); // результирующий цвет чёрный
    vec4 eyePosition = vec4(0.0, 0.0, 0.0, 1.0); // позиция наблюдателя
    vec4 diffMatColor = texture2D(u_texture, v_textcoord); // диффузный цвет
    vec3 eyeVec = normalize(v_position.xyz - eyePosition.xyz); // направление взгляда
    vec3 lightVec = normalize(v_position.xyz - u_lightPosition.xyz); // вектор освещения
    vec3 reflectLight = normalize(reflect(lightVec, v_normal)); // отражённый свет
    float len = length(v_position.xyz - eyePosition.xyz); // расстояние от наблюдателя до точки
    float specularFactor = 30.0; // размер пятна блика
    float ambientFactor = 0.1; // светимость материала
    vec4 reflectionColor = vec4(1.0, 1.0, 1.0, 1.0); //цвет блика белый

    // вариант с затуханием яркости освещения
    //vec4 diffColor = diffMatColor * u_lightPower *
    //        max(0.0, dot(v_normal, -lightVec)) / (1.0 + 0.25 * pow(len, 2.0));
    vec4 diffColor = diffMatColor * u_lightPower * max(0.0, dot(v_normal, -lightVec));
    resultColor += diffColor;

    vec4 ambientColor = ambientFactor * diffMatColor;
    resultColor += ambientColor;

    // вариант с затуханием яркости освещения
    //vec4 specularColor = reflectionColor * u_lightPower *
    //        pow(max(0.0, dot(reflectLight, -eyeVec)), specularFactor) /
    //        (1.0 + 0.25 * pow(len, 2.0));
    vec4 specularColor = reflectionColor * u_lightPower *
            pow(max(0.0, dot(reflectLight, -eyeVec)), specularFactor);
    resultColor += specularColor;

    gl_FragColor = resultColor;
}
