using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

public class ini : MonoBehaviour
{
    List<GameObject> a_bits = new List<GameObject>();
    List<GameObject> a_bits_1 = new List<GameObject>();
    List<GameObject> c_bits = new List<GameObject>();
    List<GameObject> c_bits_1 = new List<GameObject>();
    List<int> cnum = new List<int>();
    List<int> cnum_1 = new List<int>();
    List<GameObject> ans_bits = new List<GameObject>();
    List<int> ans_num = new List<int>();
    public int bit_length = 8;
    public Texture t_0;
    public Texture t_1;
    int[] num = new int[8] { 0, 1, 0, 1, 0, 1, 0, 1 };
    int[] num_1 = new int[8] { 0, 1, 1, 1, 0, 1, 0, 1 };
    List<int> c1 = new List<int> { 0, 1, 3, 4, 6 };
    List<int> c2 = new List<int> { 0, 2, 3, 5, 6 };
    List<int> c3 = new List<int> { 1, 2, 3, 7 };
    List<int> c4 = new List<int> { 4, 5, 6, 7 };
    List<List<int>> c;
    //间距时间
    float betweentime = 3f;
    //浮现时间
    float t0 = 2f;
    //第一次传输时间/距离
    float t1 = 2f; float d1 = 3;

    bool isready = false;
    //第一次trans--开始
    bool flag = true;
    //第一次trans--结束
    bool flag_t1 = false;
    //第二次的cor1结束
    bool flag_cor = false; float t2 = 2f;
    //第二次的cor2结束
    bool flag_cor2 = false; float t3 = 2f;
    //第三次的cor3 即combine
    bool flag_com = false; float t4 = 2f;
    //final cal
    bool flag_final = false; float t5 = 2f;
    void Start()
    {
        c = new List<List<int>> { c1, c2, c3, c4 };
        for (int i = 0; i < bit_length; ++i)
        {
            //动态生成bits
            GameObject tmp = GameObject.CreatePrimitive(PrimitiveType.Cube);
            a_bits.Add(tmp);
            a_bits[i].transform.parent = GameObject.Find("background").transform;
            a_bits[i].AddComponent<Renderer>();
            Renderer r1 = a_bits[i].GetComponent<Renderer>();
            Material m1 = r1.material;
            if (i % 2 == 0)
            {
                r1.material.mainTexture = t_0;
                Hamming.ham_code.Add(i);
            }
            else
            {
                r1.material.mainTexture = t_1;
                Hamming.ham_code.Add(i);
            }
            r1.material.color = Color.clear;
            m1.shader = Shader.Find("Sprites/Default");
            tmp.transform.Rotate(Vector3.forward, 180f);
            a_bits[i].transform.position = new Vector3(-16 + i * 4 + 2, 6, 3f);
            //动态挂载脚本
            a_bits[i].AddComponent<transmission>();
            a_bits[i].GetComponent<transmission>().index = i;
        }
        //flag_t1 = true;
    }
    //利用协程进行暂停
    IEnumerator Trans()
    {
        for (int i = 0; i < bit_length; ++i)
        {
            GameObject new_one;
            if (i % 2 == 0 && i != 2)
            {
                new_one = dynamic_bits.new_bits_0(a_bits[i].transform.position);
                Hamming.ham_code1.Add(0);
            }
            else
            {
                new_one = dynamic_bits.new_bits_1(a_bits[i].transform.position);
                Hamming.ham_code1.Add(1);
            }

            if (i == 2)
            {
                new_one.GetComponent<Renderer>().material.color = Color.red;
                //Hamming.ham_code1.Add()
            }
            a_bits_1.Add(new_one);
            //添加组件
            new_one.AddComponent<transmission>();
            new_one.GetComponent<transmission>().setting(new_one.transform.position - d1 * Vector3.up, t1, i == 2);
            yield return new WaitForSeconds(t1);
            Debug.Log("Remove");
        }
        yield return new WaitForSeconds(betweentime);
        flag_t1 = true;
    }
    //协程2
    IEnumerator Cor()
    {
        List<GameObject> arrows = new List<GameObject>();
        for (int i = 0; i < c.Count; ++i)
        {

            //Debug.LogError(tmp);
            //arrow
            int ans = c[i][0];
            arrows.AddRange(transmission.SDrawPath(new Vector3(-6 + i * 4, -1, 3f), a_bits[c[i][0]].transform.position));
            //Debug.LogError(i);
            for (int j = 1; j < c[i].Count; ++j)
            {
                //Debug.Log("aaaaaaaaaaaaaaa" + c[i].Count);
                Debug.LogError(c[i][j]);
                int tmp1 = num[c[i][j]];
                ans ^= tmp1;

                Debug.LogError(-6 + i * 4 + " " + a_bits[c[i][j]].transform.position.x);
                arrows.AddRange(transmission.SDrawPath(new Vector3(-6 + i * 4, -1, 3f), a_bits[c[i][j]].transform.position));
                //Debug.Log("bbbbbbbbbbbbb" + arrows.Count);

            }
            if (ans == 0) c_bits.Add(dynamic_bits.new_bits_0(new Vector3(-6 + i * 4, -1, 3f)));
            else c_bits.Add(dynamic_bits.new_bits_1(new Vector3(-6 + i * 4, -1, 3f)));
            cnum.Add(ans);
            //生成新bits
            yield return new WaitForSeconds(t2);
            int tmp = arrows.Count;
            for (int h = 0; h < tmp; ++h)
            {
                //Debug.LogError(h);
                Destroy(arrows[h]);

            }

            /*            foreach (var h in arrows)
                        {
                            //Debug.Log("bbbbbbbbbbbbb" + arrows.Count);
                            Destroy(h);
                        }*/


        }
        yield return new WaitForSeconds(betweentime);
        //cor结束
        flag_cor = true;
    }
    //协程3
    IEnumerator Cor2()
    {
        List<GameObject> arrows = new List<GameObject>();
        for (int i = 0; i < c.Count; ++i)
        {

            //Debug.LogError(tmp);
            //arrow
            int ans = c[i][0];
            arrows.AddRange(transmission.SDrawPath(new Vector3(-6 + i * 4, -3, 3f), a_bits_1[c[i][0]].transform.position));
            //Debug.LogError(i);
            for (int j = 1; j < c[i].Count; ++j)
            {
                //Debug.Log("aaaaaaaaaaaaaaa" + c[i].Count);
                Debug.LogError(c[i][j]);
                int tmp1 = num_1[c[i][j]];
                ans ^= tmp1;

                Debug.LogError(-6 + i * 4 + " " + a_bits_1[c[i][j]].transform.position.x);
                arrows.AddRange(transmission.SDrawPath(new Vector3(-6 + i * 4, -3, 3f), a_bits_1[c[i][j]].transform.position));
                //Debug.Log("bbbbbbbbbbbbb" + arrows.Count);

            }
            if (ans == 0) c_bits_1.Add(dynamic_bits.new_bits_0(new Vector3(-6 + i * 4, -3, 3f)));
            else c_bits_1.Add(dynamic_bits.new_bits_1(new Vector3(-6 + i * 4, -3, 3f)));
            cnum_1.Add(ans);
            //生成新bits
            yield return new WaitForSeconds(t3);
            int tmp = arrows.Count;
            for (int h = 0; h < tmp; ++h)
            {
                //Debug.LogError(h);
                Destroy(arrows[h]);

            }
            /*            foreach (var h in arrows)
                        {
                            //Debug.Log("bbbbbbbbbbbbb" + arrows.Count);
                            Destroy(h);
                        }*/


        }
        yield return new WaitForSeconds(betweentime);
        //cor结束
        flag_cor2 = true;
    }
    //协程4(combination)
    IEnumerator Cor3()
    {
        List<GameObject> arrows = new List<GameObject>();
        for (int i = 0; i < c_bits_1.Count; ++i)
        {
            arrows.AddRange(transmission.SDrawPath(c_bits_1[i].transform.position - Vector3.up * 2, c_bits_1[i].transform.position));
            int ans = cnum[i] ^ cnum_1[i];
            Debug.LogError(cnum[i] + " " + cnum_1[i]);
            ans_num.Add(ans);
            if (ans == 0) ans_bits.Add(dynamic_bits.new_bits_0(c_bits_1[i].transform.position - Vector3.up * 2));
            else
            {
                ans_bits.Add(dynamic_bits.new_bits_1(c_bits_1[i].transform.position - Vector3.up * 2));
            }
            yield return new WaitForSeconds(t4);
        }
        flag_com = true;
        foreach (var i in arrows)
        {
            Destroy(i);
        }
        yield return new WaitForSeconds(betweentime);
    }
    //协程5(final cal)
    IEnumerator Cor4()
    {
        List<GameObject> arrows = new List<GameObject>();
        for (int i = 0; i < ans_bits.Count; ++i)
        {
            arrows.AddRange(transmission.SDrawPath(new Vector3(0, ans_bits[i].transform.position.y - 2, ans_bits[i].transform.position.z), ans_bits[i].transform.position));
        }
        dynamic_bits.new_bits_3(new Vector3(0, ans_bits[0].transform.position.y - 2, ans_bits[0].transform.position.z));
        yield return new WaitForSeconds(t5);
        foreach (var i in arrows)
        {
            Destroy(i);
        }
        yield return new WaitForSeconds(betweentime);
        flag_final = true;
    }
    void OnGUI()
    {
        //纠错过程
        /*        if (flag_t1)
                {*/
        GUI.Button(new Rect(Screen.width / 2 - 200, 0, 400, 50), "Transmission");
        GUI.Button(new Rect(Screen.width / 2 - 200, Screen.height / 2 - 50, 400, 50), "Correction Bits");
        //.Button(new Rect(1600, 900, 200, 200), "Correction Bits");
        /*        }*/
        if (flag_final)
        {
            GUI.Button(new Rect(Screen.width / 2 - 250, Screen.height - 50, 200, 50), "Fianl answer:(the wrong bit):");
            GUI.Button(new Rect(Screen.width / 2 + 50, Screen.height - 50, 150, 50), "0110->3");
        }

    }
    // Update is called once per frame
    private float time = 0;
    void Update()
    {
        time += Time.deltaTime;
        float tmp = 1;
        if (time < t0) tmp = time / t0;
        for (int i = 0; i < bit_length; ++i)
        {
            a_bits[i].GetComponent<Renderer>().material.color = Color.Lerp(Color.clear, Color.white, tmp);
        }
        //bool flag = true;
        if (time >= t0 && flag)
        {
            StartCoroutine((IEnumerator)Trans());
            flag = false;
        }



        //计算纠错码
        if (flag_t1)
        {

            //code first
            StartCoroutine("Cor");
            //设置flag 防止帧重叠;
            flag_t1 = false;
        }
        if (flag_cor)
        {
            StartCoroutine("Cor2");
            flag_cor = false;
        }
        if (flag_cor2)
        {
            StartCoroutine("Cor3");
            flag_cor2 = false;
        }
        if (flag_com)
        {
            StartCoroutine("Cor4");
            flag_com = false;

        }
    }
}
