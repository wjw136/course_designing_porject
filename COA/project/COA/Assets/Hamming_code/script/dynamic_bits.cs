using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEditor;

/*
 * 动态生成bits
 * 工具类
 */
public class dynamic_bits : MonoBehaviour
{
    public static Texture t1;

    public static Texture t0;
    public static Texture t3;
    public static GameObject new_bits_0(Vector3 pos)
    {
        GameObject tmp = GameObject.CreatePrimitive(PrimitiveType.Cube);
        tmp.transform.parent = GameObject.Find("background").transform;
        tmp.AddComponent<Renderer>();
        Renderer r1 = tmp.GetComponent<Renderer>();
        Material m1 = r1.material;
        r1.material.mainTexture = t0;
        m1.shader = Shader.Find("Sprites/Default");
        tmp.transform.position = pos;
        //镜像原因 上下左右翻转
        tmp.transform.Rotate(Vector3.forward, 180f);
        return tmp;
    }
    public static GameObject new_bits_1(Vector3 pos)
    {
        GameObject tmp = GameObject.CreatePrimitive(PrimitiveType.Cube);
        tmp.transform.parent = GameObject.Find("background").transform;
        tmp.AddComponent<Renderer>();
        Renderer r1 = tmp.GetComponent<Renderer>();
        Material m1 = r1.material;
        r1.material.mainTexture = t1;
        m1.shader = Shader.Find("Sprites/Default");
        tmp.transform.position = pos;
        tmp.transform.Rotate(Vector3.forward, 180f);
        return tmp;
    }
    public static GameObject new_bits_3(Vector3 pos)
    {
        GameObject tmp = GameObject.CreatePrimitive(PrimitiveType.Cube);
        tmp.transform.parent = GameObject.Find("background").transform;
        tmp.AddComponent<Renderer>();
        Renderer r1 = tmp.GetComponent<Renderer>();
        Material m1 = r1.material;
        r1.material.mainTexture = t3;
        m1.shader = Shader.Find("Sprites/Default");
        tmp.transform.position = pos;
        tmp.transform.Rotate(Vector3.forward, 180f);
        return tmp;
    }
    private void Start()
    {
        //assetdatabase方法只能在start处调用----start的时候脚本才与场景联系;
        t1 = AssetDatabase.LoadAssetAtPath("Assets/_Makaka Games/Mobile Game Icon Pack/Sprites/64x64/button_score_1.png", typeof(Texture)) as Texture;
        t0 = AssetDatabase.LoadAssetAtPath("Assets/_Makaka Games/Mobile Game Icon Pack/Sprites/64x64/button_score_0.png", typeof(Texture)) as Texture;
        t3 = AssetDatabase.LoadAssetAtPath("Assets/_Makaka Games/Mobile Game Icon Pack/Sprites/64x64/button_score_3.png", typeof(Texture)) as Texture;

    }
}
